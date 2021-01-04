#include "dfpch.h"
#include "OpenGLOrthographicCamera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"

#include "DebugUtil/Instrumentation.h"
namespace Drifter
{
	void OpenGLOrthographicCamera::SetRotationEuler(float yaw, float pitch, float roll)
	{
		PROFILE_RENDERER_FUNCTION();
		//DF_LOG_INFO("Setting... Yaw {0} Pitch {1}. Matrix : {2}", yaw, pitch, glm::to_string(glm::yawPitchRoll(yaw, pitch, roll)));
		m_ForwardVector = (glm::yawPitchRoll(yaw, pitch * -1, roll) * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f)).xyz;
		m_UpVector = (glm::yawPitchRoll(yaw, pitch * -1, roll) * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)).xyz;
		//GetYawPitchRoll();
	}

	glm::vec3 OpenGLOrthographicCamera::GetYawPitchRoll() const {
		PROFILE_RENDERER_FUNCTION();
		float yaw = atan2(m_ForwardVector.x, m_ForwardVector.z);
		float pitch = glm::asin(m_ForwardVector.y);

		float roll = 0.0f; //TODO - calculate roll

		//DF_LOG_INFO("Yaw {0} Pitch {1}. Forward Vector: {2}" , yaw, pitch, glm::to_string(m_ForwardVector));
		return glm::vec3(yaw, pitch, roll);
	}

	void OpenGLOrthographicCamera::RecalculateTransforms()
	{
		PROFILE_RENDERER_FUNCTION();
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