#include "dfpch.h"
#include "Renderer.h"

#include "RenderCommand.h"
namespace Drifter {
	RendererAPI Renderer::s_RendererAPI = RendererAPI::OpenGL;
	ShaderLibrary Renderer::s_ShaderLibrary;

	void Renderer::Init() {
		RenderCommand::Init();
		LoadStartupShaders();
	}

	void Renderer::LoadStartupShaders() {
		s_ShaderLibrary.LoadNewShader("./assets/shaders/StandardShader.glsl");
	}

	void Renderer::SetClearColor(const glm::vec4 color)
	{
		RenderCommand::SetClearColor(color);
	}
	void Renderer::Clear()
	{
		RenderCommand::Clear();
	}
	void Renderer::BeginScene()
	{
	}
	void Renderer::EndScene()
	{
	}
	void Renderer::Submit(const Ref<VertexArray>& vertexArray)
	{
		RenderCommand::DrawIndexedTriangles(vertexArray);
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
		RenderCommand::SetViewport(0, 0, width, height);
	}

}