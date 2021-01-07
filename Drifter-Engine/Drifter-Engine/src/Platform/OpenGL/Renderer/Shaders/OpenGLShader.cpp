#include "dfpch.h"
#include "glad/glad.h"
#include "OpenGLShader.h"

#include <fstream>
#include "DebugUtil/Instrumentation.h"
namespace Drifter
{
	static GLenum GetType(std::string& type) {
		GLenum glType = -1; 
		if (type == "vertex") {
			glType = GL_VERTEX_SHADER;
		}
		if (type == "fragment" || type == "pixel") {
			glType = GL_FRAGMENT_SHADER;
		}
		DF_ASSERT_LV1(glType != -1, "Unknown Shader Type!");
		return glType;
	}

	static void PrintLinkingErrorLog(GLuint programID) {
		//shader compilation failed
		GLint infoLogLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* infoLog = new GLchar[infoLogLength];
		glad_glGetProgramInfoLog(programID, infoLogLength, 0, infoLog);

		DF_LOG_ERROR("Program Linking failed : {0}", infoLog);
	}


	static std::string GetFilename(const std::string& filepath) {
		size_t lastSlashIndex = filepath.find_last_of("/\\");
		lastSlashIndex = lastSlashIndex == std::string::npos ? 0 : lastSlashIndex + 1;
		size_t lastDotIndex = std::min(filepath.rfind('.'), filepath.size());

		return filepath.substr(lastSlashIndex, lastDotIndex - lastSlashIndex);
	}

	OpenGLShader::OpenGLShader(const std::string& filepath) :
		m_RendererID(0), m_Name(GetFilename(filepath))
	{
		PROFILE_RENDERER_FUNCTION();
		std::string fileContents = ReadFile(filepath);
		std::unordered_map<uint32_t, std::string> shaderSources = Preprocess(fileContents);
		this->Compile(shaderSources);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vert, const std::string& frag) :
		m_RendererID(0), m_Name(name)
	{
		PROFILE_RENDERER_FUNCTION();
		std::unordered_map<uint32_t, std::string> shaderSources;
		shaderSources[GL_VERTEX_SHADER] = vert;
		shaderSources[GL_FRAGMENT_SHADER] = frag;
		this->Compile(shaderSources);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath) const{
		PROFILE_RENDERER_FUNCTION();
		std::string result;
		std::ifstream stream;
		stream.open(filepath, std::ios::in, std::ios::binary);

		if (stream) {
			stream.seekg(0, std::ios::end);
			result.resize(stream.tellg());
			stream.seekg(0);
			stream.read(&result[0], result.size());
			stream.close();
			return result;
		}
		DF_LOG_ERROR(std::string("Failed to read the file") + filepath);
		return result;
	}

	std::unordered_map<uint32_t, std::string> OpenGLShader::Preprocess(const std::string& source) const {
		PROFILE_RENDERER_FUNCTION();
		std::unordered_map<uint32_t, std::string> sourceMap;

		std::vector<std::string> tokens;

		const char* typeToken = "#type";
		size_t pos = source.find(typeToken, 0);
		while (pos < source.length()) {
			//pos points is position of token
			pos += strlen(typeToken);
			
			size_t eofLine = std::min(source.find('\r', pos), source.find('\n', pos));
			size_t tokStart = source.find_first_not_of(" ", pos);
			size_t tokEnd = std::min(source.find(" ", tokStart), eofLine);
			GLenum glType = GetType(source.substr(tokStart, tokEnd - tokStart));
			
			//move pos to shader stage source code
			pos = std::min(source.find_first_not_of('\r', eofLine + 1), source.find_first_not_of('\n', eofLine + 1));
			size_t sourceEnd = std::min(source.find(typeToken, pos), source.length());
			sourceMap[glType] = source.substr(pos, sourceEnd - pos);
			pos = sourceEnd;
		}

		return sourceMap;

	}

	GLuint CompileShader(std::string& source, GLenum shaderType)
	{
		PROFILE_RENDERER_FUNCTION();
		GLuint shader = glCreateShader(shaderType);
		const GLchar* sourceCStr = source.c_str();
		glShaderSource(shader, 1, &sourceCStr, 0);
		glCompileShader(shader);

		int success = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			//shader compilation failed
			GLint infoLogLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar* infoLog = new GLchar[infoLogLength];
			glGetShaderInfoLog(shader, infoLogLength, 0, infoLog);

			char* sType = (shaderType == GL_FRAGMENT_SHADER ? "Fragment Shader" : "Vertex Shader");
			DF_LOG_ERROR("{1} compilation failed : {0}", infoLog, sType);

			glDeleteShader(shader);
			return -1;
		}

		return shader;
	}

	void OpenGLShader::Compile(std::unordered_map<uint32_t, std::string>& shaderSources) {
		PROFILE_RENDERER_FUNCTION();
		bool success = true;
		std::vector<int> shaders;
		for (auto& shaderSource : shaderSources) {
			int shader = CompileShader(shaderSource.second, shaderSource.first);
			if (shader == -1) {
				success = false;
				for (auto it = shaders.begin(); it != shaders.end(); it++) {
					glDeleteShader(*it);
				}
				m_RendererID = 0;
				return;
			}
			shaders.push_back(shader);
		}
		{
			PROFILE_RENDERER_SCOPE("LINK SHADERS");
			m_RendererID = glCreateProgram();
			for (auto it = shaders.begin(); it != shaders.end(); it++) {
				glAttachShader(m_RendererID, *it);
			}
			glLinkProgram(m_RendererID);

			int linkSuccess = 0;
			glGetProgramiv(m_RendererID, GL_LINK_STATUS, &linkSuccess);
			if (!linkSuccess) {
				PrintLinkingErrorLog(m_RendererID);
				glDeleteProgram(m_RendererID);
				for (auto it = shaders.begin(); it != shaders.end(); it++) {
					glDeleteShader(*it);
				}
				m_RendererID = 0;
				return;
			}

			for (auto it = shaders.begin(); it != shaders.end(); it++) {
				glDetachShader(m_RendererID, *it);
				glDeleteShader(*it);
			}
		}
	}

	void OpenGLShader::Bind()
	{
		PROFILE_RENDERER_FUNCTION();
		glUseProgram(m_RendererID);
	}
	void OpenGLShader::Unbind()
	{
		glUseProgram(0);
	}
}