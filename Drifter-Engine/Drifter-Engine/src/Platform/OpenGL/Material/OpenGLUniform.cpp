#include "dfpch.h"

#include "OpenGLUniform.h"
#include "glad/glad.h"

#include <glm/gtc/type_ptr.hpp>
namespace Drifter {
	OpenGLUniform::OpenGLUniform(Shader& shader, const char* name) 
		: m_Shader(shader), m_UniformID(0)
	{
		m_Shader.Bind();
		m_UniformID = glGetUniformLocation(m_Shader.GetID(), name);
		DF_ASSERT(m_UniformID != -1, "Failed to find uniform of name {0}. Invalid ID returned", name);
		
	}
	void OpenGLUniform::Set(float value)
	{
		m_Shader.Bind();
		glUniform1f(m_UniformID, value);
	}
	void OpenGLUniform::Set(const glm::vec2& value)
	{
		m_Shader.Bind();
		glUniform2f(m_UniformID, value.r, value.g);
	}
	void OpenGLUniform::Set(const glm::vec3& value)
	{
		m_Shader.Bind();
		glUniform3f(m_UniformID, value.r, value.g, value.b);
	}
	void OpenGLUniform::Set(const glm::vec4& value)
	{
		m_Shader.Bind();
		glUniform4f(m_UniformID, value.r, value.g, value.b, value.a);
	}
	void OpenGLUniform::Set(const glm::mat3x3& value)
	{
		m_Shader.Bind();
		glUniformMatrix3fv(m_UniformID, 1, GL_FALSE, glm::value_ptr(value));
	}
	void OpenGLUniform::Set(const glm::mat4x4& value)
	{
		m_Shader.Bind();
		glUniformMatrix4fv(m_UniformID, 1, GL_FALSE, glm::value_ptr(value));
	}
	void OpenGLUniform::Set(int value)
	{
		m_Shader.Bind();
		glUniform1i(m_UniformID, value);
	}
	void OpenGLUniform::Set(const glm::ivec2& value)
	{
		m_Shader.Bind();
		glUniform2i(m_UniformID, value.r, value.g);
	}
	void OpenGLUniform::Set(const glm::ivec3& value)
	{
		m_Shader.Bind();
		glUniform3i(m_UniformID, value.r, value.g, value.b);
	}
	void OpenGLUniform::Set(const glm::ivec4& value)
	{
		m_Shader.Bind();
		glUniform4i(m_UniformID, value.r, value.g, value.b, value.a);
	}
	void OpenGLUniform::Set(bool value)
	{
		m_Shader.Bind();
		glUniform1i(m_UniformID, static_cast<GLint>(value));
	}
	float OpenGLUniform::GetFloat()
	{
		float result = 0.0f;
		glGetUniformfv(m_Shader.GetID(), m_UniformID, &result);
		return result;
	}
	glm::vec2 OpenGLUniform::GetVec2()
	{
		float  result[2];
		glGetnUniformfv(m_Shader.GetID(), m_UniformID, 2, result);
		return glm::make_vec2(result);

	}
	glm::vec3 OpenGLUniform::GetVec3()
	{
		float  result[3];
		glGetnUniformfv(m_Shader.GetID(), m_UniformID, 3, result);
		return glm::make_vec3(result);

	}
	glm::vec4 OpenGLUniform::GetVec4()
	{
		float  result[4];
		glGetnUniformfv(m_Shader.GetID(), m_UniformID, 4, result);
		return glm::make_vec4(result);
	}
	glm::mat3x3 OpenGLUniform::GetMat3()
	{
		float  result[3 * 3];
		glGetnUniformfv(m_Shader.GetID(), m_UniformID, 3 * 3, result);
		return glm::make_mat3x3(result);
	}
	glm::mat4x4 OpenGLUniform::GetMat4()
	{
		float  result[4 * 4];
		glGetnUniformfv(m_Shader.GetID(), m_UniformID, 4 * 4, result);
		return glm::make_mat4x4(result);
	}
	int OpenGLUniform::GetInt()
	{
		int result = 0;
		glGetUniformiv(m_Shader.GetID(), m_UniformID, &result);
		return result;
	}
	glm::ivec2 OpenGLUniform::GetIVec2()
	{
		int  result[2];
		glGetnUniformiv(m_Shader.GetID(), m_UniformID, 2, result);
		return glm::ivec2(result[0], result[1]);
	}
	glm::ivec3 OpenGLUniform::GetIVec3()
	{
		int  result[3];
		glGetnUniformiv(m_Shader.GetID(), m_UniformID, 3, result);
		return glm::ivec3(result[0], result[1], result[2]);
	}
	glm::ivec4 OpenGLUniform::GetIVec4()
	{
		int  result[4];
		glGetnUniformiv(m_Shader.GetID(), m_UniformID, 4, result);
		return glm::ivec4(result[0], result[1], result[2], result[3]);
	}
	bool OpenGLUniform::GetBool()
	{
		int result = 0;
		glGetUniformiv(m_Shader.GetID(), m_UniformID, &result);
		return static_cast<bool>(result);
	}
}