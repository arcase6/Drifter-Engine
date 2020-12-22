#include "dfpch.h"
#include "OpenGLOrthographicCamera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
namespace Drifter
{
	void OpenGLOrthographicCamera::SetRotationEuler(float yaw, float pitch, float roll)
	{
		m_ForwardVector = (glm::yawPitchRoll(yaw, pitch, roll) * glm::vec4(0, 0, -1.0f, 0)).xyz;
		m_UpVector = (glm::yawPitchRoll(yaw, pitch, roll) * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)).xyz;
		RecalculateTransforms();
	}

	void OpenGLOrthographicCamera::RecalculateTransforms()
	{
		glm::vec3 target = m_Position + m_ForwardVector;
		m_ViewMatrix = glm::lookAt(
			m_Position,
			m_Position + m_ForwardVector,
			m_UpVector);

		m_ProjectionMatrix = glm::ortho(
			-m_Width / 2.0f, //left
			m_Width / 2.0f, //right
			-m_Height / 2.0f, //bottom
			m_Height / 2.0f, //top
			m_NearClip,
			m_FarClip);
	}
}