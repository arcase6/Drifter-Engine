#include "OpenGLCamera.h"

#include "glm/gtc/matrix_transform.hpp"
namespace Drifter
{
	void OpenGLPerspectiveCamera::RecalculateTransforms()
	{
		m_ViewMatrix = glm::lookAt(
			m_Position,
			m_Position + m_LookVector,
			glm::vec3(0.0f, 1.0f, 0.0f));
		
		m_ProjectionMatrix = glm::perspective(
			m_FOVRadians, //field of view in radians
			m_Width / m_Height, //aspect ratio
			m_NearClip,
			m_FarClip);
	}
	void OpenGLOrthographicCamera::RecalculateTransforms()
	{
		m_ViewMatrix = glm::lookAt(
			m_Position,
			m_Position + m_LookVector,
			glm::vec3(0.0f, 1.0f, 0.0f));

		m_ProjectionMatrix = glm::ortho(
			0.0f, //left
			m_Width, //right
			0.0f, //bottom
			m_Height, //top
			m_NearClip, 
			m_FarClip);
	}
}