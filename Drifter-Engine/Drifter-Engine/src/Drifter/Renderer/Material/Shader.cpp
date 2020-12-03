#include "Drifter/Core/dfpch.h"
#include "Shader.h"

#include "glad/glad.h"

namespace Drifter {

	GLuint CompileShader(const char* source, GLuint shaderType)
	{
		GLuint shader = glCreateShader(shaderType);
		glShaderSource(shader, 1, &source, 0);
		glCompileShader(shader);

		int success = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			//shader compilation failed
			GLint infoLogLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar * infoLog = new GLchar[infoLogLength];
			glGetShaderInfoLog(shader, infoLogLength, 0, infoLog);

			char* sType = (shaderType == GL_FRAGMENT_SHADER ? "Fragment Shader" : "Vertex Shader");
			DF_LOG_ERROR("{1} compilation failed : {0}", infoLog, sType);

			glDeleteShader(shader);
			return 0;
		}

		return shader;
	}

	void PrintLinkingErrorLog(GLuint programID) {
		//shader compilation failed
		GLint infoLogLength = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* infoLog = new GLchar[infoLogLength];
		glad_glGetProgramInfoLog(programID, infoLogLength, 0, infoLog);

		DF_LOG_ERROR("Program Linking failed : {0}", infoLog);
	}


	Shader::Shader(const char* vert, const char* frag) :
		m_RendererID(0)
	{
		GLuint vertShader, fragShader;
		bool success = (vertShader = CompileShader(vert, GL_VERTEX_SHADER)) != 0;
		success = success && ((fragShader = CompileShader(frag, GL_FRAGMENT_SHADER)) != 0);
		if (!success) {
			return;
		}

		m_RendererID = glCreateProgram();
		glAttachShader(m_RendererID, vertShader);
		glAttachShader(m_RendererID, fragShader);
		glLinkProgram(m_RendererID);

		int linkSuccess = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, &linkSuccess);
		if (!linkSuccess) {
			PrintLinkingErrorLog(m_RendererID);
			glDeleteProgram(m_RendererID);
			m_RendererID = 0;
		}


		glDetachShader(m_RendererID, vertShader);
		glDetachShader(m_RendererID, fragShader);

		glDeleteShader(vertShader);
		glDeleteShader(fragShader);
	}
	Shader::~Shader()
	{
	}
	void Shader::Bind()
	{
		glUseProgram(m_RendererID);
	}
	void Shader::UnBind()
	{
		glUseProgram(0);
	}
}
