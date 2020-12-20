#pragma once
#include "Drifter/Renderer/Material/Shader.h"
#include "OpenGLUniform.h"
namespace Drifter {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vert, const std::string& frag);
		virtual ~OpenGLShader() = default;
		virtual const std::string& GetName() const override { return m_Name; }
		virtual void Bind() override;
		virtual void UnBind() override;

		virtual inline uint32_t GetID() override {
			return m_RendererID;
		}
	protected:
		uint32_t m_RendererID;
	private:
		std::string m_Name;
	private:
		std::string ReadFile(const std::string& filepath) const;
		std::unordered_map<uint32_t, std::string> Preprocess(const std::string& filepath) const;
		void Compile(std::unordered_map<uint32_t, std::string>& shaderSources);

	public:
		// Wrapper around Uniform
		void Set(const char* name, float value) { OpenGLUniform(*this, name).Set(value); }
		void Set(const char * name, const glm::vec2& value) { OpenGLUniform(*this, name).Set(value); }
		void Set(const char * name, const glm::vec3& value) { OpenGLUniform(*this, name).Set(value); }
		void Set(const char * name, const glm::vec4& value) { OpenGLUniform(*this, name).Set(value); }
		void Set(const char * name, const glm::mat3x3& value) { OpenGLUniform(*this, name).Set(value); }
		void Set(const char * name, const glm::mat4& value) { OpenGLUniform(*this, name).Set(value); }
		void Set(const char * name, int value) { OpenGLUniform(*this, name).Set(value); }
		void Set(const char * name, const glm::ivec2& value) { OpenGLUniform(*this, name).Set(value); }
		void Set(const char * name, const glm::ivec3& value) { OpenGLUniform(*this, name).Set(value); }
		void Set(const char * name, const glm::ivec4& value) { OpenGLUniform(*this, name).Set(value); }
		void Set(const char * name, bool value) { OpenGLUniform(*this, name).Set(value); }
		float GetFloat(const char* name) { return OpenGLUniform(*this, name).GetFloat(); }
		glm::vec2 GetVec2(const char * name){ return OpenGLUniform(*this, name).GetVec2(); }
		glm::vec3 GetVec3(const char * name){ return OpenGLUniform(*this, name).GetVec3(); }
		glm::vec4 GetVec4(const char * name){ return OpenGLUniform(*this, name).GetVec4(); }
		glm::mat3x3 GetMat3(const char * name){ return OpenGLUniform(*this, name).GetMat3(); }
		glm::mat4 GetMat4(const char * name){ return OpenGLUniform(*this, name).GetMat4(); }
		int GetInt(const char * name){ return OpenGLUniform(*this, name).GetInt(); }
		glm::ivec2 GetIVec2(const char * name){ return OpenGLUniform(*this, name).GetIVec2(); }
		glm::ivec3 GetIVec3(const char * name){ return OpenGLUniform(*this, name).GetIVec3(); }
		glm::ivec4 GetIVec4(const char * name){ return OpenGLUniform(*this, name).GetIVec4(); }
		bool GetBool(const char * name){ return OpenGLUniform(*this, name).GetBool(); }
	};
}