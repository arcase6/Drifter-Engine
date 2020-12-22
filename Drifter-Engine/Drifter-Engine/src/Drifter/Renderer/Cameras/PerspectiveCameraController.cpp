#include "CameraController.h"

#include "Drifter/Input/Input.h"
#include "Drifter/Core/Time.h"

#include "Drifter/Events/MouseEvent.h"

#include "glm/gtc/constants.hpp"

namespace Drifter {

	void PerspectiveCameraController::OnUpdate()
	{
		if (!Application::Get().GetWindow().GetCaptureMouseFlag()) {
			return;
		}
		glm::vec3 posDelta = glm::vec3(0.0f, 0.0f, 0.0f);
		float rotDelta = 0.0f;
		if (Input::IsKeyPressed(KeyCodes::W())) {
			posDelta += GetForwardVector();
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
			posDelta -= glm::vec3(0.0f, 1.0f, 0.0f); //GetUpVector();
		}
		else if (Input::IsKeyPressed(KeyCodes::E())) {
			posDelta += glm::vec3(0.0f, 1.0f, 0.0f); //GetUpVector();
		}

		if (Input::IsKeyPressed(KeyCodes::NUM_2())) {
			rotDelta = 1.0f;
		}
		else if (Input::IsKeyPressed(KeyCodes::NUM_3())) {
			rotDelta = -1.0f;
		}

		if (Input::IsKeyPressed(KeyCodes::LEFT_SHIFT())) {
			posDelta *= 3.0f;
		}

		posDelta *= Time::GetDeltaTime() * m_Speed;
		rotDelta *= Time::GetDeltaTime() * m_Speed * glm::pi<float>() / 2.0f;
		
		m_YawPitchRoll.z += rotDelta;
		
		m_Camera->SetPosition(m_Camera->GetPosition() + posDelta);
		m_Camera->SetRotationEuler(m_YawPitchRoll.x, m_YawPitchRoll.y, m_YawPitchRoll.z);


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
		m_YawPitchRoll += glm::vec3(deltaPosition.x * -1, deltaPosition.y * -1, 0.0f);

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

		if (e.GetKeyCode() == KeyCodes::NUM_1() && window->GetCaptureMouseFlag()) {
			m_YawPitchRoll.z = 0.0f;
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
}