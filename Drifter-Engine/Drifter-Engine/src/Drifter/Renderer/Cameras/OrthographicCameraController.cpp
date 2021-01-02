#include "CameraController.h"

#include "Drifter/Input/Input.h"
#include "Drifter/Core/Time.h"

#include "Drifter/Events/MouseEvent.h"

#include "glm/gtc/constants.hpp"
#include "glm/gtx/string_cast.hpp"

#include "Debug/Instrumentation.h"
namespace Drifter {
	void OrthorgraphicCameraController::OnUpdate()
	{
		PROFILE_FUNCTION();
		glm::vec3 posDelta = glm::vec3(0.0f, 0.0f, 0.0f);
		float rotDelta = 0.0f;
		//DF_LOG_INFO("Right Vector : {0} , Up Vector : {1}", glm::to_string(m_Camera->GetRightVector()), glm::to_string(m_Camera->GetUpVector()));
		if (Input::IsKeyPressed(KeyCodes::W())) {
			posDelta += m_Camera->GetUpVector();
		}
		else if (Input::IsKeyPressed(KeyCodes::S())) {
			posDelta -= m_Camera->GetUpVector();
		}
		
		if (Input::IsKeyPressed(KeyCodes::A())) {
			posDelta -= m_Camera->GetRightVector();
		}
		else if (Input::IsKeyPressed(KeyCodes::D())) {
			posDelta += m_Camera->GetRightVector();
		}

		if (Input::IsKeyPressed(KeyCodes::Q())) {
			rotDelta -= 1.0f;
		}
		else if (Input::IsKeyPressed(KeyCodes::E())) {
			rotDelta += 1.0f;
		}

		posDelta *= Time::GetDeltaTime() * m_Speed * m_ZoomLevel;
		m_YawPitchRoll.z += (Time::GetDeltaTime() * rotDelta * glm::pi<float>() / 2.0f);

		m_Camera->SetPosition(m_Camera->GetPosition() + posDelta);
		m_Camera->SetRotationEuler(m_YawPitchRoll.x, m_YawPitchRoll.y, m_YawPitchRoll.z);

		m_Camera->RecalculateTransforms();
	}
	void OrthorgraphicCameraController::OnEvent(Event& e)
	{
		PROFILE_FUNCTION();
		EventDispatcher d(e);
		d.Dispatch<MouseScrolledEvent>(std::bind(&OrthorgraphicCameraController::OnMouseScrolled, this, std::placeholders::_1));
		d.Dispatch<WindowResizeEvent>(std::bind(&OrthorgraphicCameraController::OnWindowResize, this, std::placeholders::_1));
		d.Dispatch<KeyPressedEvent>(std::bind(&OrthorgraphicCameraController::OnKeyPressed, this, std::placeholders::_1));
	}

	bool OrthorgraphicCameraController::OnMouseScrolled(MouseScrolledEvent& e) {
		float zoomSpeed = .15f;
		m_ZoomLevel = std::max(0.25f, m_ZoomLevel * (1 - e.GetYOffset() * zoomSpeed));

		m_Camera->SetZoomAndAspectRatio(m_ZoomLevel, m_AspectRatio);
		m_Camera->RecalculateTransforms();
		return true;
	}

	bool OrthorgraphicCameraController::OnWindowResize(WindowResizeEvent& e) {
		
		PROFILE_FUNCTION();
		m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		m_Camera->SetZoomAndAspectRatio(m_ZoomLevel, m_AspectRatio);
		m_Camera->RecalculateTransforms();
		return false;
	}

	bool OrthorgraphicCameraController::OnKeyPressed(KeyPressedEvent& e) {

		PROFILE_FUNCTION();
		if (e.GetKeyCode() == KeyCodes::NUM_1()) {
			m_YawPitchRoll.z = 0.0f;
			return true;
		}

		return false;
	}


	Ref<CameraController> CameraController::CreateOrthographic(Ref<OrthographicCamera> camera, float speed)
	{
		CameraController* controller = new OrthorgraphicCameraController(camera, speed);
		return Ref<CameraController>(controller);
	}
}