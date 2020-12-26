#pragma once

#include "VertexArray.h"
#include "Drifter/Renderer/Shaders/Shader.h"
#include "glm/glm.hpp"

#include "Drifter/Renderer/Cameras/Camera.h"
namespace Drifter {
	enum class RendererAPI
	{
		None = 0, OpenGL = 1
	};
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();

		static void SetClearColor(const glm::vec4 color);
		static void Clear();

		static void BeginScene(const Camera& camera);
		static void EndScene();

		static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform);

		static void OnWindowResize(uint32_t width, uint32_t height);
		
		inline static ShaderLibrary& GetShaderLibrary() { return s_ShaderLibrary; }
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
		static ShaderLibrary s_ShaderLibrary;

		static void LoadStartupShaders();
	};
}