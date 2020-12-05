#include "Drifter/Core/dfpch.h"
#include "Shader.h"
#include "Drifter/Renderer/Renderer.h"

#include "Platform/OpenGL/Material/OpenGLShader.h"
namespace Drifter {
	Shader* Shader::Create(const char* vert, const char* frag) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			DF_LOG_ERROR("RendererAPI::None is not currently implemented!");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLShader(vert, frag);
		}
		DF_LOG_ERROR("Unsupported RendererAPI received!");
		return nullptr;
	}
}
