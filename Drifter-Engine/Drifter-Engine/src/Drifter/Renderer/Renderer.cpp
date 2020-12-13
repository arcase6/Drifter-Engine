#include "Drifter/Core/dfpch.h"
#include "Renderer.h"

#include "RenderCommand.h"
namespace Drifter {
	RendererAPI Renderer::s_RendererAPI = RendererAPI::OpenGL;
	
	void Renderer::Init() {
		RenderCommand::Init();
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
}