#pragma once
#include "Drifter.h"

#include "Drifter/Camera/CameraController.h"

namespace Sandbox{
	class Sandbox2DLayer : public Drifter::Layer
	{

	public:
		Sandbox2DLayer() : Layer("Sandbox2D") {}

		//Inheritted from Layer
		virtual void OnUpdate() override;
		virtual void OnImgui() override;

		virtual void OnEvent(Drifter::Event& e) override;

		virtual void OnAttach() override {
			//m_MainTex = Drifter::Texture2D::Create("./assets/textures/Checkerboard.png");
			m_MainTex = Drifter::Texture2D::Create("./assets/textures/Spiral.png");
			SetupCameras();
			SetupTilemap();
		}
		
	private:
		void SetupCameras();
		void SetupTilemap();
		void DrawGrid();
		void DrawSpriteAtlas();
		void DrawTilemap();
		void DrawImguiProfiling();
	private:


		//OpenGL data for rendering -- likely to be removed later
		Drifter::Ref<Drifter::Texture2D> m_MainTex, m_OverlayTex;

		Drifter::Ref<Drifter::Camera> m_Camera;
		Drifter::Ref<Drifter::CameraController> m_CameraController;
		glm::vec4 m_Tint = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		float m_Rotation = 0.0f; //radians
		glm::vec2 m_Size { 1.0f , 1.0f};

		glm::ivec2 m_GridSize{ 10,10 };
		glm::vec2 m_Pivot{0.0f, 0.0f };

		glm::vec2 m_Tiling{ 1.0f, 1.0f };
		glm::vec2 m_Offset{ 0.0f, 0.0f };

		Drifter::Ref<Drifter::UniformTextureAtlas> m_Atlas;
		Drifter::Ref<Drifter::Tilemap> m_Tilemap;
		Drifter::Ref<Drifter::Tilemap> m_TilemapOverlay;

	};
}

