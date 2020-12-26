#include "dfpch.h"
#include "Drifter/Renderer/Renderer2D.h"
#include "Drifter/Renderer/Renderer.h"
#include "Drifter/Renderer/RenderCommand.h"

#include "Platform/OpenGL/Renderer/Shaders/OpenGLShader.h"
#include "Drifter/Renderer/Shaders/Texture.h"

#include "glm/gtc/matrix_transform.hpp"
namespace Drifter {

	struct SceneData2D {
		SceneData2D()
			:
			ViewProjectionMatrix(1.0)
		{
		}
		glm::mat4 ViewProjectionMatrix;
		Ref<Shader> SpriteShader;
		Ref<Texture2D> DefaultTexture;
		Ref<VertexArray> QuadVertexArray;
	};

	static SceneData2D* Data;

	void Renderer2D::Init() {
		Data = new SceneData2D();
		Data->SpriteShader = Renderer::GetShaderLibrary().FindShader("SpriteShader");
		Data->DefaultTexture = Texture2D::Create(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 1);

		std::vector<float> vertices =
		{
			 0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
			 1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			 0.0f,  0.0f,  0.0f,  0.0f, 1.0f,

			 0.0f,  -1.0f, 0.0f,  0.0f, 0.0f,
			 1.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			 1.0f, 0.0f,   0.0f,  1.0f, 1.0f,
		};
		std::vector<uint32_t> indices;
		for (int i = 0; i < vertices.size(); i++) {
			indices.push_back(i);
		}

		Drifter::BufferLayout layout = {
			{ Drifter::ShaderDataType::Float3, "a_Position" },
			{ Drifter::ShaderDataType::Float2, "a_UV" }
		};
		Data->QuadVertexArray.reset(Drifter::VertexArray::Create(vertices, indices, layout));
	}

	void Renderer2D::Shutdown() {
		delete Data;

	}

	void Renderer2D::BeginScene(const Camera& camera)
	{
		Data->ViewProjectionMatrix = camera.GetProjectionMatrix() * camera.GetViewMatrix();
		Data->SpriteShader->Bind();
	}
	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::OnWindowResize(uint32_t width, uint32_t height) {

	}

	void Renderer2D::DrawQuad(const glm::vec2& topLeft, const glm::vec2& size, const glm::vec4 color) {
		DrawQuad({ topLeft.x, topLeft.y, 0.0f }, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3& topLeft, const glm::vec2& size, const glm::vec4 color) {
		Data->SpriteShader->Bind();
		auto shader = std::dynamic_pointer_cast<OpenGLShader>(Data->SpriteShader);

		glm::mat4 modelTransform = glm::translate(glm::mat4(1.0f), topLeft);

		shader->Set("u_ViewProjection", Data->ViewProjectionMatrix);
		shader->Set("u_Model", modelTransform);
		shader->Set("u_Tint", color);

		Data->DefaultTexture->Bind(0);

		RenderCommand::DrawIndexedTriangles(Data->QuadVertexArray);
	}
}