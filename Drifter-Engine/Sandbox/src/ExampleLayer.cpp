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
		m_Shader.reset(dynamic_cast<Drifter::OpenGLShader*>(Drifter::Shader::Create("./assets/shaders/StandardShader.glsl")));
		m_MainTex = Drifter::Texture2D::Create("./assets/textures/Checkerboard.png");
		m_OverlayTex = Drifter::Texture2D::Create("./assets/textures/Spiral.png");
	}

	void ExampleLayer::SetupCameras() {

		//SetupCamera
		m_CameraPosition = glm::vec3(0.0f, 0.0f, 1.0f);
		m_Camera.reset(static_cast<Drifter::Camera*>(
			Drifter::PerspectiveCamera::Create(m_CameraPosition, glm::vec3(0.0f, 0.0f, 1.0f), 60.0)
			));
		m_Camera->SetNearClipDistance(0.01f);
		m_Camera->SetFarClipDistance(1000.0f);

		m_Camera->SetLookVector(glm::vec3(0.0f, 0.0f, -1.0f));
		m_Camera->RecalculateTransforms();
	}

	void ExampleLayer::OnUpdate()
	{
		using namespace Drifter;
		static glm::mat4 triangleTransform = glm::mat4(1);
		
		static glm::vec3 boxPosition = glm::vec3(0,0,-5.0f);
		static glm::mat4 boxTransform = glm::translate(glm::mat4(1), boxPosition);

		//move camera here
		glm::vec3 posDelta = glm::vec3(0.0f, 0.0f, 0.0f);
		if (Input::IsKeyPressed(KeyCodes::W())) {
			posDelta.y = 1.0f;
		}
		else if (Input::IsKeyPressed(KeyCodes::S())) {
			posDelta.y = -1.0f;
		}
		if (Input::IsKeyPressed(KeyCodes::A())) {
			posDelta.x = -1.0f;
		}
		else if (Input::IsKeyPressed(KeyCodes::D())) {
			posDelta.x = 1.0f;
		}

		static float movementPerSecond = 1.0f;
		posDelta *= Time::GetDeltaTime() * movementPerSecond;

		m_CameraPosition = m_Camera->GetPosition() + posDelta;
		m_Camera->SetPosition(m_CameraPosition);
		m_Camera->RecalculateTransforms();

		glm::mat4 viewMatrix = m_Camera->GetViewMatrix();
		glm::mat4 projectionMatrix = m_Camera->GetProjectionMatrix();


		//DF_LOG_INFO("position : {0}", glm::to_string(m_Camera->GetPosition()));
		//DF_LOG_INFO("delta  : {0}", glm::to_string(posDelta));
		//DF_LOG_INFO("deltaTime  : {0}", Time::GetDeltaTime());
		//DF_LOG_INFO("View Matrix {0}", glm::to_string(viewMatrix));
		//DF_LOG_INFO("Projection Matrix {0}" , glm::to_string(projectionMatrix));

		//projectionMatrix = glm::mat4(1.0f);
		glm::mat4 vpMatrix = projectionMatrix * viewMatrix;
		

		m_Box->Bind();
		m_Shader->Bind();
		m_Shader->Set("u_Model", boxTransform);
		m_MainTex->Bind(0);
		Renderer::Submit(m_Box);

		m_Triangle->Bind();
		m_Shader->Bind();
		m_Shader->Set("u_Time", static_cast<float>(Time::GetTime()));
		m_Shader->Set("u_ViewProjection", vpMatrix);
		m_Shader->Set("u_Model", triangleTransform);
		m_OverlayTex->Bind(0);
		Renderer::Submit(m_Triangle);

		


	}

	void ExampleLayer::OnEvent(Drifter::Event& e)
	{
	}
}