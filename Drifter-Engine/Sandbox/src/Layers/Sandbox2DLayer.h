#pragma once
#include "Drifter.h"

#include "Drifter/Renderer/Cameras/CameraController.h"

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
			SetupCameras();
		}
		
	private:
		void SetupCameras();
	private:

		//OpenGL data for rendering -- likely to be removed later
		Drifter::Ref<Drifter::Texture2D> m_MainTex, m_OverlayTex;

		Drifter::Ref<Drifter::Camera> m_Camera;
		Drifter::Ref<Drifter::CameraController> m_CameraController;
		glm::vec4 m_Tint = glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
		float m_Rotation = 0.0f; //radians
		glm::vec2 m_Size { 1.0f , 1.0f};
	};
}

