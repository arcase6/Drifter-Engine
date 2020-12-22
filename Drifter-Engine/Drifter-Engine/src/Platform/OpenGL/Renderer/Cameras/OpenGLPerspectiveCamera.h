#pragma once

#include "Drifter/Renderer/Cameras/Camera.h"
#include "Drifter/Application.h"

namespace Drifter {
	class OpenGLPerspectiveCamera : public PerspectiveCamera
	{
	public:
		OpenGLPerspectiveCamera(float aspectRatio, float fovDegrees)
			:m_Position(glm::vec3(0.0f, 0.0f, 0.0f)),
			m_ForwardVector(glm::vec3(1.0f, 0.0f, 0.0f)),
			m_NearClip(0.3f),
			m_FarClip(1000.0f),
			m_AspectRatio(aspectRatio),
			m_ViewMatrix(glm::mat4(1.0)),
			m_ProjectionMatrix(glm::mat4(1.0)),
			m_FOVRadians(glm::radians(fovDegrees)),
			m_UpVector(0.0f, 1.0f, 0.0f)
		{ }

		//Base Camera Implementation
		virtual glm::vec3 GetPosition() const override { return m_Position; }
		virtual void SetPosition(const glm::vec3& position) override { m_Position = position; }

		virtual float GetAspectRatio() const override { return m_AspectRatio; }
		virtual void SetAspectRatio(float aspectRatio) override { m_AspectRatio = aspectRatio; }

		virtual void LookAt(const glm::vec3& target) override { SetForwardVector(target - m_Position); }
		virtual void SetForwardVector(const glm::vec3& lookVector) override {
			m_ForwardVector = glm::normalize(lookVector); 
			glm::vec3 rightVector = glm::cross(lookVector, glm::vec3(0, 1, 0));
			m_UpVector = glm::cross(rightVector, m_ForwardVector);
		}
		virtual void SetRotationEuler(float yaw, float pitch, float roll) override;
		
		virtual glm::vec3 GetForwardVector() const override { return m_ForwardVector; }
		virtual glm::vec3 GetUpVector() const override { return m_UpVector; }
		virtual glm::vec3 GetRightVector() const override { return glm::cross(m_ForwardVector, m_UpVector); }


		virtual glm::mat4 GetViewMatrix() const override { return m_ViewMatrix; }
		virtual glm::mat4 GetProjectionMatrix() const override { return m_ProjectionMatrix; }

		virtual float GetNearClipDistance() const override { return m_NearClip; }
		virtual void SetNearClipDistance(float distance) override { m_NearClip = distance; }

		virtual float GetFarClipDistance() const override { return m_FarClip; }
		virtual void SetFarClipDistance(float distance) override { m_FarClip = distance; }

		virtual void RecalculateTransforms() override;

		//Perspective Camera Implementation
		virtual float GetFOVDegrees() const override { return m_FOVRadians; }
		virtual void SetFOVDegrees(float value) override { m_FOVRadians = glm::radians(value); }

		virtual float GetFOVRadians() const override { return m_FOVRadians; }
		virtual void SetFOVRadians(float value) override { m_FOVRadians = value; }
	private:
		//Base fields
		glm::vec3 m_Position;
		glm::vec3 m_ForwardVector;
		glm::vec3 m_UpVector;

		float m_AspectRatio;

		float m_NearClip;
		float m_FarClip;

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;

		//Perspective Camera fields
		float m_FOVRadians;
	 };
}

