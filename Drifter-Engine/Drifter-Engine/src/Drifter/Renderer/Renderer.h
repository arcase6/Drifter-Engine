#pragma once

#include "VertexArray.h"
#include "Drifter/Renderer/Shaders/Shader.h"
#include "glm/glm.hpp"

namespace Drifter {
	enum class RendererAPI
	{
		None = 0, OpenGL = 1
	};
	class Renderer
	{
	public:
		static void Init();

		static void SetClearColor(const glm::vec4 color);
		static void Clear();

		static void BeginScene();
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray);
		
		inline static ShaderLibrary& GetShaderLibrary() { return s_ShaderLibrary; }
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
		static ShaderLibrary s_ShaderLibrary;

		static void LoadStartupShaders();
	};
}