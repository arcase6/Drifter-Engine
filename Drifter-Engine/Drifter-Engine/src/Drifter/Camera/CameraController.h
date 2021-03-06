#pragma once

#include "Drifter/Events/Event.h"
#include "Drifter/Events/ApplicationEvent.h"
#include "Drifter/Events/MouseEvent.h"
#include "Drifter/Events/KeyEvent.h"

#include "Camera.h"
#include "glm/glm.hpp"

namespace Drifter {

	class CameraController
	{
	public:
		virtual ~CameraController() = default;

		virtual void OnUpdate() = 0;
		virtual void OnEvent(Event& e) = 0;
	
	public:
		virtual glm::vec3 GetForwardVector() const = 0;
		virtual glm::vec3 GetRightVector() const = 0;
		virtual glm::vec3 GetUpVector() const = 0;
		
		static Ref<CameraController> CreateOrthographic(Ref<OrthographicCamera> camera, float speed);
		static Ref<CameraController> CreatePerspective(Ref<PerspectiveCamera> camera, float speed);
	};

	class OrthorgraphicCameraController : public CameraController
	{
	public:
		OrthorgraphicCameraController(Ref<OrthographicCamera> camera, float speed)
			:m_Camera(camera),
			m_Speed(speed),
			m_ZoomLevel(camera->GetZoomLevel()),
			m_AspectRatio(camera->GetWidth() / camera->GetHeight()),
			m_YawPitchRoll(camera->GetYawPitchRoll())
		{}
		virtual void OnUpdate() override;
		
		virtual void OnEvent(Event& e) override;
		
		virtual glm::vec3 GetForwardVector() const override { return m_Camera->GetForwardVector(); }
		virtual glm::vec3 GetRightVector() const override{ return m_Camera->GetRightVector();}
		virtual glm::vec3 GetUpVector() const override { return m_Camera->GetUpVector(); }

	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
			
	private:
		Ref<OrthographicCamera> m_Camera;
		float m_Speed;
		float m_ZoomLevel;
		float m_AspectRatio;
		glm::vec3 m_YawPitchRoll;
	};

	class PerspectiveCameraController : public CameraController
	{
	public:
		PerspectiveCameraController(Ref<PerspectiveCamera> camera, float speed)
			:m_Camera(camera), m_Speed(speed), m_YawPitchRoll(camera->GetYawPitchRoll()), m_LastPosition(0)
		{}

		virtual void OnUpdate() override;
		virtual void OnEvent(Event& e) override;

		virtual glm::vec3 GetForwardVector() const override { return m_Camera->GetForwardVector(); }
		virtual glm::vec3 GetRightVector() const override { return m_Camera->GetRightVector(); }
		virtual glm::vec3 GetUpVector() const override { return m_Camera->GetUpVector(); }
	private:
		bool OnMouseMoved(MouseMovedEvent& e);
		bool OnMouseButton(MouseButtonPressedEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Ref<PerspectiveCamera> m_Camera;
		float m_Speed;
		glm::vec2 m_LastPosition;
		glm::vec3 m_YawPitchRoll;
	};
}
