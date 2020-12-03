#pragma once
#include "Drifter.h"

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
		std::shared_ptr<Drifter::VertexArray> m_VertexArray;
		std::unique_ptr<Drifter::Shader> m_Shader;
		std::unique_ptr<Drifter::Uniform> u_time;
		std::unique_ptr<Drifter::Uniform> u_VP;


		std::unique_ptr<Drifter::Camera> camera;
		glm::vec3 m_CameraPosition;
	};
}