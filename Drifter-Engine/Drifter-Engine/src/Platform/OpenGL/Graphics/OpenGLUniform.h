#pragma once
#include "Drifter/Graphics/Uniform.h"
namespace Drifter {
	class OpenGLUniform : public Uniform
	{
	public:
		OpenGLUniform(Shader& owner, const char* name);
		
		// Interface implementation of Uniform

		//Setters
		virtual void Set(float value) override;
		virtual void Set(const glm::vec2& value) override;
		virtual void Set(const glm::vec3& value) override;
		virtual void Set(const glm::vec4& value) override;

		virtual void Set(const glm::mat3x3& value) override;
		virtual void Set(const glm::mat4& value) override;

		virtual void Set(int32_t value) override;
		virtual void Set(const glm::ivec2& value) override;
		virtual void Set(const glm::ivec3& value) override;
		virtual void Set(const glm::ivec4& value) override;
		virtual void Set(const int32_t* value, uint32_t count) override;


		virtual void Set(bool value) override;

		//Getters
		virtual float GetFloat() override;
		virtual glm::vec2 GetVec2() override;
		virtual glm::vec3 GetVec3() override;
		virtual glm::vec4 GetVec4() override;
		
		virtual glm::mat3 GetMat3() override;
		virtual glm::mat4 GetMat4() override;
		
		virtual int GetInt() override;
		virtual glm::ivec2 GetIVec2() override;
		virtual glm::ivec3 GetIVec3() override;
		virtual glm::ivec4 GetIVec4() override;
		
		virtual bool GetBool() override;

	private:
		Shader& m_Shader;
		uint32_t m_UniformID;
	};
}

