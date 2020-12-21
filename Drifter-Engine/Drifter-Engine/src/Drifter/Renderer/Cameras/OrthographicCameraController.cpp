#include "CameraController.h"

#include "Drifter/Input/Input.h"
#include "Drifter/Core/Time.h"

#include "Drifter/Events/MouseEvent.h"

#include "glm/gtc/constants.hpp"

namespace Drifter {
	void OrthorgraphicCameraController::OnUpdate()
	{
		glm::vec3 posDelta = glm::vec3(0.0f, 0.0f, 0.0f);
		if (Input::IsKeyPressed(KeyCodes::W())) {
			posDelta.y = 1.0f;
		}
		else if (Input::IsKeyPressed(KeyCodes::S())) {
			posDelta.y = -1.0f;
		}
		if (Input::IsKeyPressed(KeyCodes::A())) {
			posDelta.x = -1.0f;
		}
		else if (Input::IsKeyPressed(KeyCodes::D())) {
			posDelta.x = 1.0f;
		}

		posDelta *= Time::GetDeltaTime() * m_Speed * m_ZoomLevel;

		m_Camera->SetPosition(m_Camera->GetPosition() + posDelta);
		m_Camera->RecalculateTransforms();
	}
	void OrthorgraphicCameraController::OnEvent(Event& e)
	{
		EventDispatcher d(e);
		d.Dispatch<MouseScrolledEvent>(std::bind(&OrthorgraphicCameraController::OnMouseScrolled, this, std::placeholders::_1));
		d.Dispatch<WindowResizeEvent>(std::bind(&OrthorgraphicCameraController::OnWindowResize, this, std::placeholders::_1));
	}

	bool OrthorgraphicCameraController::OnMouseScrolled(MouseScrolledEvent& e) {
		float zoomSpeed = .15f;
		m_ZoomLevel = std::max(0.25f, m_ZoomLevel * (1 - e.GetYOffset() * zoomSpeed));

		m_Camera->SetZoomAndAspectRatio(m_ZoomLevel, m_AspectRatio);
		m_Camera->RecalculateTransforms();
		return true;
	}

	bool OrthorgraphicCameraController::OnWindowResize(WindowResizeEvent& e) {
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera->SetZoomAndAspectRatio(m_ZoomLevel, m_AspectRatio);
		m_Camera->RecalculateTransforms();
		return false;
	}

	Ref<CameraController> CameraController::CreateOrthographic(Ref<OrthographicCamera> camera, float speed)
	{
		CameraController* controller = new OrthorgraphicCameraController(camera, speed);
		return Scope<CameraController>(controller);
	}
	Ref<CameraController> CameraController::CreatePerspective(Ref<PerspectiveCamera> camera, float speed)
	{
		CameraController* controller = new PerspectiveCameraController(camera, speed);
		return Scope<CameraController>(controller);
	}
}