#pragma once

#include "glm/glm.hpp"
#include "Shader.h"
namespace Drifter {
	class Uniform
	{
	public:
		const char* Name;

		static Uniform * Create(Shader& shader,const char* name);
		virtual ~Uniform() = default;

		//setters
		virtual void Set(float value) = 0;
		virtual void Set(const glm::vec2& value) = 0;
		virtual void Set(const glm::vec3& value) = 0;
		virtual void Set(const glm::vec4& value) = 0;

		virtual void Set(const glm::mat3x3& value) = 0;
		virtual void Set(const glm::mat4& value) = 0;

		virtual void Set(int value) = 0;
		virtual void Set(const glm::ivec2& value) = 0;
		virtual void Set(const glm::ivec3& value) = 0;
		virtual void Set(const glm::ivec4&  value) = 0;

		virtual void Set(bool value) = 0;

		//getters
		virtual float       GetFloat() = 0;
		virtual glm::vec2   GetVec2()  = 0;
		virtual glm::vec3   GetVec3()  = 0;
		virtual glm::vec4   GetVec4()  = 0;
									   
		virtual glm::mat3 GetMat3()  = 0;
		virtual glm::mat4 GetMat4()  = 0;

		virtual int         GetInt()   = 0;
		virtual glm::ivec2  GetIVec2() = 0;
		virtual glm::ivec3  GetIVec3() = 0;
		virtual glm::ivec4  GetIVec4() = 0;

		virtual bool        GetBool()  = 0;
	};
}

