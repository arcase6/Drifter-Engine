#include "Sandbox2DLayer.h"

#include "Platform/OpenGL/Renderer/Shaders/OpenGLShader.h"
#include "Drifter/Renderer/Cameras/CameraController.h"

#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"
namespace Sandbox {

	void Sandbox2DLayer::SetQuadData()
	{
		std::vector<float> vertices =
		{
			-0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
			 0.5f, -0.5f,  0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.0f,  1.0f, 1.0f,
						   
			 0.5f,  0.5f,  0.0f,  1.0f, 1.0f,
			-0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.0f,  0.0f, 0.0f,
		};
		std::vector<uint32_t> indices;
		for (int i = 0; i < vertices.size(); i++) {
			indices.push_back(i);
		}

		Drifter::BufferLayout layout = {
			{ Drifter::ShaderDataType::Float3, "a_Position" },
			{ Drifter::ShaderDataType::Float2, "a_UV" }
		};
		m_Quad.reset(Drifter::VertexArray::Create(vertices, indices, layout));
	}

	void Sandbox2DLayer::SetupShaders()
	{
		m_MainTex = Drifter::Texture2D::Create(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1,1);
	}

	void Sandbox2DLayer::SetupCameras() {

		//SetupCamera
		glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, -100.0f);
		glm::vec3 lookVector = glm::vec3(0.0f, 0.0f, 1.0f);

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
		ImGui::End();
	}

	void Sandbox2DLayer::OnUpdate()
	{

		using namespace Drifter;
		static glm::mat4 boxTransform = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5.0f));

		//move camera here
		m_CameraController->OnUpdate();

		glm::mat4 viewMatrix = m_Camera->GetViewMatrix();
		glm::mat4 projectionMatrix = m_Camera->GetProjectionMatrix();

		glm::mat4 vpMatrix = projectionMatrix * viewMatrix;

		m_Quad->Bind();

		Ref<OpenGLShader> shader = std::dynamic_pointer_cast<OpenGLShader>(Renderer::GetShaderLibrary().FindShader("SpriteShader"));

		shader->Bind();
		shader->Set("u_ViewProjection", vpMatrix);
		shader->Set("u_Model", boxTransform);
		shader->Set("u_Tint", m_Tint);
		m_MainTex->Bind(0);
		Renderer::Submit(m_Quad);
	}

	void Sandbox2DLayer::OnEvent(Drifter::Event& e)
	{
		m_CameraController->OnEvent(e);
	}
}