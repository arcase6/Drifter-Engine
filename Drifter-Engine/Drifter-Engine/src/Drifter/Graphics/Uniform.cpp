#include "dfpch.h"
#include "Uniform.h"

#include "Drifter/Renderer/Renderer.h"
#include "Platform/OpenGL/Graphics/OpenGLUniform.h"
namespace Drifter {
	Uniform * Uniform::Create(Shader& shader, const char* name) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			DF_LOG_ERROR("RendererAPI::None is not currently implemented!");
			return nullptr;
		case RendererAPI::OpenGL:
			return static_cast<Uniform*>(new OpenGLUniform(shader, name));
		}
		DF_LOG_ERROR("Unsupported RendererAPI received!");
		return nullptr;
	}

}