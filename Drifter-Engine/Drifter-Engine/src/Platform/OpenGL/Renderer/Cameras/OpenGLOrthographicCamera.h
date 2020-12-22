#pragma once

#include "Drifter/Renderer/Cameras/Camera.h"
#include "Drifter/Application.h"

namespace Drifter
{
	class OpenGLOrthographicCamera : public OrthographicCamera
	{
	public:
		OpenGLOrthographicCamera(float width, float height) :
			m_Position(glm::vec3(0.0f, 0.0f, 0.0f)),
			m_ForwardVector(glm::vec3(1.0f, 0.0f, 0.0f)),
			m_NearClip(0.3f),
			m_FarClip(1000.0f),
			m_Width(width),
			m_Height(height),
			m_ViewMatrix(glm::mat4(1.0)),
			m_ProjectionMatrix(glm::mat4(1.0)),
			m_UpVector(0, 1, 0)
		{ }

		//Base Camera Implementation
		virtual glm::vec3 GetPosition() const override { return m_Position; }
		virtual void SetPosition(const glm::vec3& position) override { m_Position = position; }

		virtual void SetDimensions(float width, float height)
		{
			m_Width = width;
			m_Height = height;
		}
		virtual void SetZoomAndAspectRatio(float zoomLevel, float aspectRatio) {
			m_Width = aspectRatio * zoomLevel;
			m_Height = zoomLevel;
		}

		virtual float GetWidth() const override { return m_Width; }
		virtual float GetHeight() const override { return m_Height; }

		virtual float GetZoomLevel() const { return m_Width; }
		virtual float GetAspectRatio() const { return m_Width / m_Height; }

		virtual void LookAt(const glm::vec3& target) override { SetForwardVector(target - m_Position); }
		virtual void SetForwardVector(const glm::vec3& forwardVector) override {
			m_ForwardVector = glm::normalize(forwardVector); 
			auto right = glm::cross(m_ForwardVector, glm::vec3(0, 1, 0));
			m_UpVector = glm::cross(right, m_ForwardVector);
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

	private:
		//BaseCamera fields
		glm::vec3 m_Position;
		glm::vec3 m_ForwardVector;
		glm::vec3 m_UpVector;

		float m_NearClip;
		float m_FarClip;

		float m_Width;
		float m_Height;

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
	};
}

