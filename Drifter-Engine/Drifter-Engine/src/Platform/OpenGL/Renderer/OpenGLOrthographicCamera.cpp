#include "dfpch.h"
#include "OpenGLOrthographicCamera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
namespace Drifter
{
	void OpenGLOrthographicCamera::SetRotationEuler(float yaw, float pitch, float roll)
	{
		glm::vec4 direction = glm::yawPitchRoll(yaw, pitch, roll) * glm::vec4(0, 0, 1, 0);
		m_LookVector = direction.xyz;
		RecalculateTransforms();
	}

	void OpenGLOrthographicCamera::RecalculateTransforms()
	{
		glm::vec3 target = m_Position + m_LookVector;
		m_ViewMatrix = glm::lookAt(
			m_Position,
			m_Position + m_LookVector,
			glm::vec3(0.0f, 1.0f, 0.0f));

		m_ProjectionMatrix = glm::ortho(
			-m_Width / 2.0f, //left
			m_Width / 2.0f, //right
			-m_Height / 2.0f, //bottom
			m_Height / 2.0f, //top
			m_NearClip,
			m_FarClip);
	}
}