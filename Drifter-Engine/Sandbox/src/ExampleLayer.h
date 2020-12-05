#pragma once
#include "Drifter.h"

#include "Platform/OpenGL/Material/OpenGLShader.h"
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
		void ExampleLayer::SetTriangleData();
		void ExampleLayer::SetBoxData();
		void ExampleLayer::SetupShaders();
		void ExampleLayer::SetupCameras();

		//Inheritted from Layer
		void OnUpdate() override;
		void OnEvent(Drifter::Event& e) override;

	private:
		//OpenGL data for rendering -- likely to be removed later
		Drifter::Ref<Drifter::VertexArray> m_Triangle;
		Drifter::Ref<Drifter::VertexArray> m_Box;
		Drifter::Ref<Drifter::OpenGLShader> m_Shader;

		Drifter::Scope<Drifter::Camera> m_Camera;
		glm::vec3 m_CameraPosition;
	};
}