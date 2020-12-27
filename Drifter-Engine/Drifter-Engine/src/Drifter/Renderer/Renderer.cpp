#include "dfpch.h"
#include "Renderer.h"

#include "RenderCommand.h"
#include "Drifter/Renderer/Renderer2D.h"
namespace Drifter {
	RendererAPI Renderer::s_RendererAPI = RendererAPI::OpenGL;
	ShaderLibrary Renderer::s_ShaderLibrary;

	struct SceneData {
		SceneData() : ViewProjectionMatrix(1.0) {}
		glm::mat4 ViewProjectionMatrix;
	};
	static SceneData * Data;

	void Renderer::Init() {
		RenderCommand::Init();
		Data = new SceneData();
		LoadStartupShaders();

		Renderer2D::Init();
	}
	
	void Renderer::Shutdown() {
		delete Data;
		Renderer2D::Shutdown();

	}

	void Renderer::LoadStartupShaders() {
		s_ShaderLibrary.LoadNewShader("./assets/shaders/StandardShader.glsl");
		s_ShaderLibrary.LoadNewShader("./assets/shaders/SpriteShader.glsl");
	}

	void Renderer::SetClearColor(const glm::vec4 color)
	{
		RenderCommand::SetClearColor(color);
	}
	void Renderer::Clear()
	{
		RenderCommand::Clear();
	}
	void Renderer::BeginScene(const Camera& camera)
	{
		Data->ViewProjectionMatrix = camera.GetProjectionMatrix() * camera.GetViewMatrix();
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", Data->ViewProjectionMatrix);
		shader->SetMat4("u_Model", transform);

		RenderCommand::DrawIndexedTriangles(vertexArray);
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
		RenderCommand::SetViewport(0, 0, width, height);
	}

}