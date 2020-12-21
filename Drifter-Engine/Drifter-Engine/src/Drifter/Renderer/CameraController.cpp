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

	void PerspectiveCameraController::OnUpdate()
	{
		glm::vec3 posDelta = glm::vec3(0.0f, 0.0f, 0.0f);
		if (Input::IsKeyPressed(KeyCodes::W())) {
			posDelta += GetForwardVector() ;
		}
		else if (Input::IsKeyPressed(KeyCodes::S())) {
			posDelta -= GetForwardVector();
		}

		if (Input::IsKeyPressed(KeyCodes::A())) {
			posDelta -= GetRightVector();
		}
		else if (Input::IsKeyPressed(KeyCodes::D())) {
			posDelta += GetRightVector();
		}
		
		if (Input::IsKeyPressed(KeyCodes::Q())) {
			posDelta -= GetUpVector();
		}
		else if (Input::IsKeyPressed(KeyCodes::E())) {
			posDelta += GetUpVector();
		}

		if (Input::IsKeyPressed(KeyCodes::LEFT_SHIFT())) {
			posDelta *= 3.0f;
		}

		posDelta *= Time::GetDeltaTime() * m_Speed;

		m_Camera->SetPosition(m_Camera->GetPosition() + posDelta);
		m_Camera->RecalculateTransforms();
	}
	void PerspectiveCameraController::OnEvent(Event& e)
	{
		EventDispatcher d(e);
		d.Dispatch<MouseMovedEvent>(std::bind(&PerspectiveCameraController::OnMouseMoved, this, std::placeholders::_1));
		d.Dispatch<MouseButtonPressedEvent>(std::bind(&PerspectiveCameraController::OnMouseButton, this, std::placeholders::_1));
		d.Dispatch<KeyPressedEvent>(std::bind(&PerspectiveCameraController::OnKeyPressed, this, std::placeholders::_1));
		d.Dispatch<WindowResizeEvent>(std::bind(&PerspectiveCameraController::OnWindowResize, this, std::placeholders::_1));
	}
	bool PerspectiveCameraController::OnMouseMoved(MouseMovedEvent& e)
	{
		auto window = &Application::Get().GetWindow();
		if (!window->GetCaptureMouseFlag()) {
			return false;
		}
		const float sensitivity = 0.005f;
		glm::vec2 currentPosition = glm::vec2(e.GetX(), e.GetY());
		glm::vec2 deltaPosition = currentPosition - m_LastPosition;
		m_LastPosition = currentPosition;

		deltaPosition *= sensitivity;
		m_YawPitchRoll += glm::vec3(deltaPosition.x * -1 , deltaPosition.y * -1, 0.0f);

		float range = glm::half_pi<float>() * 2 / 3;
		m_YawPitchRoll.y = glm::clamp(m_YawPitchRoll.y, range * -1, range);

		m_Camera->SetRotationEuler(m_YawPitchRoll.x, m_YawPitchRoll.y, m_YawPitchRoll.z);

		return false;
	}
	bool PerspectiveCameraController::OnMouseButton(MouseButtonPressedEvent& e) {
		auto window = &Application::Get().GetWindow();
		if (e.GetMouseButton() == MouseCodes::BUTTON_1() && !window->GetCaptureMouseFlag()) {
			m_LastPosition = glm::vec2(Input::GetMouseX(), Input::GetMouseY());

			window->SetCaptureMouseFlag(true);
			return true;
		}

		return false;
	}
	bool PerspectiveCameraController::OnKeyPressed(KeyPressedEvent& e) {
		auto window = &Application::Get().GetWindow();
		if (e.GetKeyCode() == KeyCodes::ESCAPE() && window->GetCaptureMouseFlag()) {
			window->SetCaptureMouseFlag(false);
			return true;
		}

		return false;
	}

	bool PerspectiveCameraController::OnWindowResize(WindowResizeEvent& e) {
		float aspectRatio = Application::Get().GetWindow().GetAspectRatio();
		m_Camera->SetAspectRatio(aspectRatio);
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