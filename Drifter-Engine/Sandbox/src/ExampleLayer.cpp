#include "ExampleLayer.h"

namespace Sandbox
{
	void ExampleLayer::SetBufferData()
	{
		std::vector<float> vertices =
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};
		std::vector<uint32_t> indices = {
			0, 1, 2
		};
		Drifter::BufferLayout layout = {
			{ Drifter::ShaderDataType::Float3, "a_Position" }
		};
		m_VertexArray.reset(Drifter::VertexArray::Create(vertices, indices, layout));
	}
	
	void ExampleLayer::SetupShaders()
	{
		const char* vert = R"(
			#version 330 core
			
			layout(location=0) in vec3 a_Position;
			out vec3 v_Position;
			
			uniform mat4 u_vp;

			void main(){
				gl_Position = u_vp * vec4(a_Position, 1.0);
				v_Position = gl_Position.xyz;
			}
		)";

		const char* frag = R"(
			#version 330 core

			layout(location=0) out vec4 fragColor;
			in vec3 v_Position;
			
			uniform float u_time;			

			void main(){
				vec3 col = vec3(1,1,1) * sin(u_time) / 2. + .5;
				float r = v_Position.x + .5;
				float g = 1 - r;
				float b = v_Position.y + .5;
				vec3 posCol = vec3(r,g,b);
				fragColor = vec4(col * posCol, 1.0);
			}
		)";

		m_Shader.reset(new Drifter::Shader(vert, frag));

		//Create unitforms for shader
		u_time.reset(Drifter::Uniform::Create(*m_Shader, "u_time"));
		u_VP.reset(Drifter::Uniform::Create(*m_Shader, "u_vp"));
	}
	
	void ExampleLayer::SetupCameras() {

		//SetupCamera
		m_CameraPosition = glm::vec3(0.0f, 0.0f, 1.0f);
		camera.reset(static_cast<Drifter::Camera*>(
			Drifter::OrthographicCamera::Create(m_CameraPosition, glm::vec3(0.0f, 0.0f, -1.0f))
			));
		camera->SetNearClipDistance(0.01f);
		camera->SetFarClipDistance(2.0f);
		camera->SetWidth(2);
		camera->SetHeight(2);
		camera->RecalculateTransforms();
	}
	
	void ExampleLayer::OnUpdate()
	{
		using namespace Drifter;
		static float movementPerSecond = 1;

		//move camera here
		glm::vec2 posDelta = glm::vec2(0.0f, 0.0f);
		if (Input::IsKeyPressed(KeyCodes::W())) {
			posDelta.y = 1.0f;
		}
		else if(Input::IsKeyPressed(KeyCodes::S())){
			posDelta.y = -1.0f;
		}
		if (Input::IsKeyPressed(KeyCodes::A())) {
			posDelta.x = -1.0f;
		}
		else if(Input::IsKeyPressed(KeyCodes::D())){
			posDelta.x = 1.0f;
		}

		posDelta *= Time::GetDeltaTime() * movementPerSecond;

		m_CameraPosition = camera->GetPosition() + glm::vec3(posDelta, 0);
		camera->SetPosition(m_CameraPosition);
		camera->RecalculateTransforms();

		glm::mat4 viewMatrix = camera->GetViewMatrix();
		glm::mat4 projectionMatrix = camera->GetProjectionMatrix();


		//DF_LOG_INFO("position : {0}", glm::to_string(camera->GetPosition()));
		//DF_LOG_INFO("delta  : {0}", glm::to_string(posDelta));
		//DF_LOG_INFO("View Matrix {0}", glm::to_string(viewMatrix));
		//DF_LOG_INFO("Projection Matrix {0}" , glm::to_string(projectionMatrix));

		//projectionMatrix = glm::mat4(1.0f);
		glm::mat4 vpMatrix = projectionMatrix * viewMatrix;


		m_VertexArray->Bind();

		m_Shader->Bind();
		u_time->Set(static_cast<float>(Time::GetTime()));
		u_VP->Set(vpMatrix);

		Renderer::Submit(m_VertexArray);
	}
	
	void ExampleLayer::OnEvent(Drifter::Event& e)
	{
	}
}