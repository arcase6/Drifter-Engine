#include "dfpch.h"
#include "OpenGLPerspectiveCamera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"

#include "glm/gtx/string_cast.hpp"

#include "Debug/Instrumentation.h"
namespace Drifter
{
	void OpenGLPerspectiveCamera::SetRotationEuler(float yaw, float pitch, float roll)
	{
		PROFILE_RENDERER_FUNCTION();
		//DF_LOG_INFO("Setting... Yaw {0} Pitch {1}. Matrix : {2}", yaw, pitch, glm::to_string(glm::yawPitchRoll(yaw, pitch, roll)));
		m_ForwardVector = (glm::yawPitchRoll(yaw, pitch* -1, roll) * glm::vec4(0.0f, 0.0f, 1.0f, 0.0f)).xyz;
		m_UpVector      = (glm::yawPitchRoll(yaw, pitch * -1, roll) * glm::vec4(0.0f, 1.0f, 0.0f, 0.0f)).xyz;
		//GetYawPitchRoll();
	}

	glm::vec3 OpenGLPerspectiveCamera::GetYawPitchRoll() const{
		PROFILE_RENDERER_FUNCTION();
		float yaw = atan2(m_ForwardVector.x, m_ForwardVector.z);
		float pitch = glm::asin(m_ForwardVector.y);

		float roll = 0.0f; //TODO - calculate roll

		//DF_LOG_INFO("Yaw {0} Pitch {1}. Forward Vector: {2}" , yaw, pitch, glm::to_string(m_ForwardVector));
		return glm::vec3(yaw,pitch,roll);
	}

	void OpenGLPerspectiveCamera::RecalculateTransforms()
	{
		PROFILE_RENDERER_FUNCTION();
		m_ViewMatrix = glm::lookAt(
			m_Position,
			m_Position + m_ForwardVector,
			m_UpVector);
		
		m_ProjectionMatrix = glm::perspective(
			m_FOVRadians,
			m_AspectRatio, 
			m_NearClip,
			m_FarClip);
	}
}