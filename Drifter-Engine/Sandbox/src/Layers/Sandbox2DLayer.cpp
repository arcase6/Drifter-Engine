#include "Sandbox2DLayer.h"
#include "Drifter.h"

#include "Platform/OpenGL/Graphics/OpenGLShader.h"
#include "Drifter/Camera/CameraController.h"
#include "Drifter/Renderer/Renderer2D.h"

#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"

#include <string>
namespace Sandbox {

	void Sandbox2DLayer::SetupCameras() {
		PROFILE_FUNCTION();
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
		ImGui::DragFloat2("Quad Size", glm::value_ptr(m_Size),.01f, .1f, 10.0f);
		ImGui::DragFloat2("Quad Pivot", glm::value_ptr(m_Pivot),.01f, 0.0f, 1.0f);

		ImGui::Spacing();
		ImGui::Text("Tiling Properties");
		ImGui::DragFloat2("Tiling", glm::value_ptr(m_Tiling), .01f, -1000.0f, 1000.0f);
		ImGui::DragFloat2("Offset", glm::value_ptr(m_Offset), .01f, -1000.0f, 1000.0f);
		ImGui::End();


		ImGui::Begin("Stats");

		auto& stats = Drifter::Renderer2D::GetStats();
		if (ImGui::CollapsingHeader("Renderer2D")) {
			ImGui::Text(fmt::format("Draw   Count: {0}", stats.DrawCount).c_str());
			ImGui::Text(fmt::format("Quad   Count: {0}", stats.QuadCount).c_str());
			ImGui::Text(fmt::format("Vertex Count: {0}", stats.GetVertexCount()).c_str());
			ImGui::Text(fmt::format("Index  Count: {0}", stats.GetIndexCount()).c_str());
		}
		stats.Reset();
#if DF_PROFILE_LEVEL >= DF_PROFILE_LEVEL_BASIC
		DrawImguiProfiling();
#endif
		ImGui::End();
	}

	void Sandbox2DLayer::DrawImguiProfiling() {
		static int ProfilingFramesRemaining = -1000;
		static int profilingDuration = 10;


		if (ProfilingFramesRemaining <= 0 && Drifter::Instrumentor::HasActiveSession()) {
			if (ProfilingFramesRemaining == -1000) {
				ProfilingFramesRemaining = profilingDuration;
			}
			else {
				END_PROFILING_SESSION();
			}
		}
		if (ImGui::CollapsingHeader("Profiler")) {
			if (!Drifter::Instrumentor::HasActiveSession()) {
				ImGui::Text("Press the . key to start a session");
				ImGui::InputInt("Frame Count", &profilingDuration);
				ProfilingFramesRemaining = -1000;
			}
			else {
				--ProfilingFramesRemaining;
				auto& profileResults = Drifter::Instrumentor::GetActiveSession()->GetLog();
				for (const auto& result : profileResults) {
					std::string message = result.Name + std::string(":") + std::to_string(result.GetDuration());
					ImGui::Text(message.c_str());
				}
			}
		}
	}

	void Sandbox2DLayer::OnUpdate()
	{
		PROFILE_FUNCTION();
		using namespace Drifter;
		//move camera here
		{
			m_CameraController->OnUpdate();
		}

		Renderer2D::BeginScene(*m_Camera);
		DrawGrid();
		Renderer2D::EndScene();

	}

	void Sandbox2DLayer::DrawGrid()
	{

		Drifter::Sprite sprite{ m_MainTex, {m_Tiling, m_Offset}, m_Tint };
		PROFILE_FUNCTION();
		using namespace Drifter;
		m_MainTex->Bind(0);
		RectTransform transform({ 0,0 }, m_Size, m_Rotation, m_Pivot);
		for (int r = 0; r < m_GridSize.x; r++) {
			for (int c = 0; c < m_GridSize.y; c++) {
				transform.SetPosition({ m_Size.x * 1.1f * c, m_Size.y * 1.1f * r , 0 });
				Renderer2D::DrawSprite(transform, sprite);
			}
		}
	}

	void Sandbox2DLayer::OnEvent(Drifter::Event& e)
	{
		m_CameraController->OnEvent(e);
	}
}