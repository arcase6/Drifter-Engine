#pragma once
#include "Core.h"
#include <unordered_map>

#include "glm/glm.hpp"
namespace Drifter {

	class Shader
	{
	public:
		static Ref<Shader> Create(const std::string& filepath);
		static Ref<Shader> Create(const std::string& name, const std::string& vert, const std::string& frag);
		virtual ~Shader() = default;
		
		virtual const std::string& GetName() const = 0;
		virtual void Bind() = 0;
		virtual void UnBind() = 0;

		virtual uint32_t GetID() = 0;

		//Set functions
		virtual void SetFloat(const char* name, float value) = 0;
		virtual void SetVec2(const char* name, const glm::vec2& value) = 0; 
		virtual void SetVec3(const char* name, const glm::vec3& value) = 0; 
		virtual void SetVec4(const char* name, const glm::vec4& value) = 0;
		
		virtual void SetMat3(const char* name, const glm::mat3& value) = 0; 
		virtual void SetMat4(const char* name, const glm::mat4& value) = 0;
		
		virtual void SetInt(const char* name, int value) = 0;
		virtual void SetIVec2(const char* name, const glm::ivec2& value) = 0;
		virtual void SetIVec3(const char* name, const glm::ivec3& value) = 0;
		virtual void SetIVec4(const char* name, const glm::ivec4& value) = 0;
		
		virtual void SetBool(const char* name, bool value) = 0;

	protected:
		uint32_t m_RendererID;
	};

	class ShaderLibrary
	{
	public:
		void RegisterExistingShader(const Ref<Shader> shader);
		void LoadNewShader(const std::string & filepath);
		Ref<Shader> FindShader(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_shaders;
	};
}

