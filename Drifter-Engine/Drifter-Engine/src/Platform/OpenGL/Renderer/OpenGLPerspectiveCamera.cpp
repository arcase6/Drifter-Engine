#include "dfpch.h"
#include "OpenGLPerspectiveCamera.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"
namespace Drifter
{
	void OpenGLPerspectiveCamera::SetRotationEuler(float yaw, float pitch, float roll)
	{
		glm::vec4 direction = glm::yawPitchRoll(yaw, pitch, roll) * glm::vec4(0,0,-1.0,0);
		m_ForwardVector = direction.xyz;
		RecalculateTransforms();
		
	}
	void OpenGLPerspectiveCamera::RecalculateTransforms()
	{
		m_ViewMatrix = glm::lookAt(
			m_Position,
			m_Position + m_ForwardVector,
			glm::vec3(0.0f, 1.0f, 0.0f));
		
		m_ProjectionMatrix = glm::perspective(
			m_FOVRadians,
			m_AspectRatio, 
			m_NearClip,
			m_FarClip);
	}
}