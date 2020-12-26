#include "ExampleLayer.h"

namespace Sandbox
{
	void ExampleLayer::SetTriangleData()
	{
		std::vector<float> vertices =
		{
			-0.5f, -0.5f, 0.0f,	 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f,	 1.0f, 0.0f,
			0.0f, 0.5f, 0.0f,    0.5f, 1.0f,
		};
		std::vector<uint32_t> indices = {
			0, 1, 2
		};
		Drifter::BufferLayout layout = {
			{ Drifter::ShaderDataType::Float3, "a_Position" },
			{ Drifter::ShaderDataType::Float2, "a_UV" }

		};
		m_Triangle.reset(Drifter::VertexArray::Create(vertices, indices, layout));
	}

	void ExampleLayer::SetBoxData()
	{
		std::vector<float> vertices =
		{
			//bottom face
			-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	        
			//top face
	        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	        
			//left face
	        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	        
			 //right face
	         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	        
			 //back face
	        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	        
			//front face
	        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f


		};
		std::vector<uint32_t> indices;
		for (int i = 0; i < vertices.size(); i++) {
			indices.push_back(i);
		}

		Drifter::BufferLayout layout = {
			{ Drifter::ShaderDataType::Float3, "a_Position" },
			{ Drifter::ShaderDataType::Float2, "a_UV" }
		};
		m_Box.reset(Drifter::VertexArray::Create(vertices, indices, layout));
	}

	void ExampleLayer::SetupShaders()
	{
		m_MainTex = Drifter::Texture2D::Create("./assets/textures/Checkerboard.png");
		m_OverlayTex = Drifter::Texture2D::Create("./assets/textures/Spiral.png");
	}

	void ExampleLayer::SetupCameras() {

		//SetupCamera
		glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, -20.0f);
		glm::vec3 lookVector = glm::vec3(0.0f, 0.0f, 1.0f);
		auto camera = Drifter::PerspectiveCamera::Create(cameraPosition, lookVector);
		//auto camera = Drifter::OrthographicCamera::CreateByAspectRatio(m_CameraPosition, glm::vec3(0.0f, 0.0f, -1.0f));
		m_Camera = std::static_pointer_cast<Drifter::Camera>(camera);
		m_Camera->SetNearClipDistance(0.01f);
		m_Camera->SetFarClipDistance(1000.0f);

		m_Camera->RecalculateTransforms();

		m_CameraController = Drifter::CameraController::CreatePerspective(camera, 2.0f);
		//m_CameraController = Drifter::CameraController::CreateOrthographic(camera, 2.0f);
	}

	void ExampleLayer::OnUpdate()
	{
		using namespace Drifter;
		static glm::mat4 triangleTransform = glm::mat4(1);
		static glm::mat4 boxTransform = glm::translate(glm::mat4(1), {0, 0, -5.0f});

		//move camera here
		m_CameraController->OnUpdate();
		
		Ref<OpenGLShader> shader = std::dynamic_pointer_cast<OpenGLShader>(Renderer::GetShaderLibrary().FindShader("StandardShader"));
		
		m_MainTex->Bind(0);

		Renderer::BeginScene(*m_Camera);
		Renderer::Submit(shader, m_Box, boxTransform);

		shader->Bind();
		shader->Set("u_Time", static_cast<float>(Time::GetTime()));
		m_OverlayTex->Bind(0);
		Renderer::Submit(shader, m_Triangle, triangleTransform);

		Renderer::EndScene();
	}

	void ExampleLayer::OnEvent(Drifter::Event& e)
	{
		m_CameraController->OnEvent(e);
	}
}