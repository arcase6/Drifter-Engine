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

	void Sandbox2DLayer::SetupTilemap() {
		auto spriteSheet = Drifter::Texture2D::Create("./assets/textures/mapPack_tilesheet.png");
		m_Atlas = Drifter::CreateRef<Drifter::UniformTextureAtlas>(spriteSheet, glm::ivec2(64));

		const char* tilemapData =
			"ggggssssss"
			"ddddddssss"
			"ggggsddddd"
			"ggggsdssss"
			"ggggsdssss"
			"ggggsdssss"
			"ggggsdssss"
			"ggggsdssss"
			"ggggsdssss"
			"ggggsdssss";
		
			m_Tilemap = Drifter::CreateRef<Drifter::Tilemap>(tilemapData, 10);
			m_Tilemap->SetRule('d', m_Atlas->GetSprite({ 6, 6 }));
			m_Tilemap->SetRule('s', m_Atlas->GetSprite({ 11, 6 }));
			m_Tilemap->SetRule('g', m_Atlas->GetSprite({ 6, 10 }));

			tilemapData =
				"xxxxxxxxxx"
				"xxexxxxrxr"
				"xttxxxxxxx"
				"xttxxpcxxx"
				"xxxxxxxxcx"
				"rxxxxxcxxx"
				"xrxxxxrxxx"
				"xtxxxxxxxx"
				"xtxxxxxxrx"
				"xxxxxxxxxx";

			m_TilemapOverlay = Drifter::CreateRef<Drifter::Tilemap>(tilemapData, 10);
			m_TilemapOverlay->SetRule('p', m_Atlas->GetSprite({ 15, 1 }));
			m_TilemapOverlay->SetRule('e', m_Atlas->GetSprite({ 16, 2 }));
			m_TilemapOverlay->SetRule('t', m_Atlas->GetSprite({ 9, 4 }));
			m_TilemapOverlay->SetRule('r', m_Atlas->GetSprite({ 8, 9 }));
			m_TilemapOverlay->SetRule('c', m_Atlas->GetSprite({ 4, 9 }));

	}

	void Sandbox2DLayer::OnUpdate()
	{
		using namespace Drifter;
		PROFILE_FUNCTION();
		//move camera here
		{
			m_CameraController->OnUpdate();
		}

		Renderer2D::BeginScene(*m_Camera);
		//DrawGrid();
		m_Tilemap->Draw();
		m_TilemapOverlay->Draw(1.0f);
		//DrawSpriteAtlas();
		Renderer2D::EndScene();

	}

	void Sandbox2DLayer::DrawGrid()
	{
		using namespace Drifter;
		PROFILE_FUNCTION();

		Drifter::Sprite sprite{ m_MainTex, {m_Tiling, m_Offset}, m_Tint };
		RectTransform transform({ 0,0 }, m_Size, m_Rotation, m_Pivot);
		for (int r = 0; r < m_GridSize.x; r++) {
			for (int c = 0; c < m_GridSize.y; c++) {
				transform.SetPosition({ m_Size.x * 1.1f * c, m_Size.y * 1.1f * r , 0 });
				Renderer2D::DrawSprite(transform, sprite);
			}
		}
	}

	void Sandbox2DLayer::DrawSpriteAtlas() {
		using namespace Drifter;
		PROFILE_FUNCTION();

		glm::ivec2 dim = m_Atlas->GetSpriteDimensions();
		RectTransform transform({ 0,0 }, m_Size, m_Rotation, m_Pivot);
		for (int y = 0; y < dim.y; ++y) {
			for (int x = 0; x < dim.x; ++x) {
				transform.SetPosition({ m_Size.x * 1.1f * x, m_Size.y * 1.1f * y , 0 });
				auto& sprite = m_Atlas->GetSprite({ x,y });
				Renderer2D::DrawSprite(transform, sprite);
			}
		}
	}
	void Sandbox2DLayer::OnEvent(Drifter::Event& e)
	{
		m_CameraController->OnEvent(e);
	}
}