#pragma once

#include "Drifter/Renderer/Camera.h"
#include "Drifter/Application.h"

namespace Drifter {
	class OpenGLCamera : virtual public Camera
	{
	public:

		OpenGLCamera() :
			m_Position(glm::vec3(0.0f,0.0f,0.0f)),
			m_LookVector(glm::vec3(1.0f,0.0f,0.0f)),
			m_NearClip(0.3f),
			m_FarClip(1000.0f),
			m_Width(static_cast<float>(Application::Get().GetWindow().GetWidth())),
			m_Height(static_cast<float>(Application::Get().GetWindow().GetWidth())),
			m_ViewMatrix(glm::mat4(1.0)),
			m_ProjectionMatrix(glm::mat4(1.0))
		{ }

		// Inherited via Camera
		virtual void SetPosition(const glm::vec3& position) override { m_Position = position; }

		virtual void SetLookVector(const glm::vec3& lookVector) override { m_LookVector = glm::normalize(lookVector); }

		virtual float GetWidth() const override { return m_Width;}
		virtual float GetHeight() const override { return m_Height; }

		virtual void SetWidth(float width) override { m_Width = width; }
		virtual void SetHeight(float height) override { m_Height = height; }

		virtual void LookAt(const glm::vec3& target) override { SetLookVector(target - m_Position); }

		virtual glm::vec3 GetPosition() const override { return m_Position; }

		virtual glm::mat4 GetViewMatrix() const override { return m_ViewMatrix; }

		virtual glm::mat4 GetProjectionMatrix() const override { return m_ProjectionMatrix; }

		virtual float GetNearClipDistance() const override { return m_NearClip; }

		virtual void SetNearClipDistance(float distance) override { m_NearClip = distance; }

		virtual float GetFarClipDistance() const override { return m_FarClip; }

		virtual void SetFarClipDistance(float distance) override { m_FarClip = distance; }

	protected:
		glm::vec3 m_Position;
		glm::vec3 m_LookVector;

		float m_NearClip;
		float m_FarClip;

		float m_Width;
		float m_Height;

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;

	};


	class OpenGLPerspectiveCamera : public OpenGLCamera, public PerspectiveCamera
	{
	public:
		OpenGLPerspectiveCamera()
			:OpenGLCamera(),
			m_FOVRadians(glm::radians(60.0f))
		{ }
		virtual float GetFOVDegrees() const override { return m_FOVRadians; }
		virtual void SetFOVDegrees(float value) override { m_FOVRadians = glm::radians(value); }

		virtual float GetFOVRadians() const override { return m_FOVRadians; }
		virtual void SetFOVRadians(float value) override { m_FOVRadians = value; }

		virtual void RecalculateTransforms() override;
	private:
		float m_FOVRadians;
	};

	class OpenGLOrthographicCamera : public OpenGLCamera, public OrthographicCamera
	{
	public:
		OpenGLOrthographicCamera() : OpenGLCamera()
		{}

		virtual void RecalculateTransforms() override;
	};
}

