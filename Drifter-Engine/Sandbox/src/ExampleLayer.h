#pragma once
#include "Drifter.h"

#include "Platform/OpenGL/Material/OpenGLShader.h"
namespace Sandbox {
	class ExampleLayer : public Drifter::Layer
	{
	public:
		ExampleLayer() : Layer("Example") {

			SetBufferData();
			SetupShaders();
			SetupCameras();
		}
		void ExampleLayer::SetBufferData();
		void ExampleLayer::SetupShaders();
		void ExampleLayer::SetupCameras();

		//Inheritted from Layer
		void OnUpdate() override;
		void OnEvent(Drifter::Event& e) override;

	private:
		//OpenGL data for rendering -- likely to be removed later
		Drifter::Ref<Drifter::VertexArray> m_VertexArray;
		Drifter::Ref<Drifter::OpenGLShader> m_Shader;

		Drifter::Scope<Drifter::Camera> camera;
		glm::vec3 m_CameraPosition;
	};
}