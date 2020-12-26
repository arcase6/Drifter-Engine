#pragma once
#include "Drifter.h"

#include "Platform/OpenGL/Renderer/Shaders/OpenGLShader.h"
#include "Drifter/Renderer/Cameras/CameraController.h"

namespace Sandbox {
	class ExampleLayer : public Drifter::Layer
	{
	public:
		ExampleLayer() : Layer("Example") {

			SetTriangleData();
			SetBoxData();
			SetupShaders();
			SetupCameras();
		}
		void SetTriangleData();
		void SetBoxData();
		void SetupShaders();
		void SetupCameras();

		//Inheritted from Layer
		void OnUpdate() override;
		void OnEvent(Drifter::Event& e) override;

	private:
		//OpenGL data for rendering -- likely to be removed later
		Drifter::Ref<Drifter::VertexArray> m_Triangle;
		Drifter::Ref<Drifter::VertexArray> m_Box;
		Drifter::Ref<Drifter::Texture2D> m_MainTex, m_OverlayTex;

		Drifter::Ref<Drifter::Camera> m_Camera;
		Drifter::Ref<Drifter::CameraController> m_CameraController;
	};
}