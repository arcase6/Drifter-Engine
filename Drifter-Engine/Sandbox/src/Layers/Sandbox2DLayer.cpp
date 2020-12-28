#include "Sandbox2DLayer.h"

#include "Platform/OpenGL/Renderer/Shaders/OpenGLShader.h"
#include "Drifter/Renderer/Cameras/CameraController.h"
#include "Drifter/Renderer/Renderer2D.h"

#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"
namespace Sandbox {	

	void Sandbox2DLayer::SetupCameras() {

		//SetupCamera
		glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 100.0f);
		glm::vec3 lookVector = glm::vec3(0.0f, 0.0f, -1.0f);

		auto camera = Drifter::OrthographicCamera::CreateByAspectRatio(cameraPosition, lookVector, 5.0f);
		m_Camera = std::static_pointer_cast<Drifter::Camera>(camera);
		m_Camera->SetNearClipDistance(0.01f);
		m_Camera->SetFarClipDistance(1000.0f);

		m_Camera->RecalculateTransforms();
		m_CameraController = Drifter::CameraController::CreateOrthographic(camera, 2.0f);
	}

	void Sandbox2DLayer::OnImgui()
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit4("Quad Tint", glm::value_ptr(m_Tint));

		ImGui::SliderInt2("Grid Size", glm::value_ptr(m_GridSize), 0, 100);
		
		ImGui::Text("Quad Transform Settings");
		ImGui::SliderAngle("Quad Rotation", &m_Rotation);
		ImGui::SliderFloat2("Quad Size", glm::value_ptr(m_Size), .1, 10);
		ImGui::SliderFloat2("Quad Pivot", glm::value_ptr(m_Pivot),0.0f, 1.0f);

		ImGui::End();
	}

	void Sandbox2DLayer::OnUpdate()
	{

		using namespace Drifter;
		//move camera here
		m_CameraController->OnUpdate();

		Renderer2D::BeginScene(*m_Camera);

		for (int r = 0; r < m_GridSize.x; r++) {
			for (int c = 0; c < m_GridSize.y; c++) {
				RectTransform transform({ m_Size.x * 1.1f * c, m_Size.y * 1.1f * r}, m_Size, m_Rotation,m_Pivot);
				Renderer2D::DrawQuad(transform, m_Tint, m_MainTex);
			}
		}

		Renderer2D::EndScene();

	}

	void Sandbox2DLayer::OnEvent(Drifter::Event& e)
	{
		m_CameraController->OnEvent(e);
	}
}