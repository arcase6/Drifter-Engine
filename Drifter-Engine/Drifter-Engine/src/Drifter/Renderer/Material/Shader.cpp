#include "Drifter/Core/dfpch.h"
#include "Shader.h"
#include "Drifter/Renderer/Renderer.h"

#include "Platform/OpenGL/Material/OpenGLShader.h"
namespace Drifter {
	Shader * Shader::Create(const char* filepath) {
		std::shared_ptr<Shader> result;
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			DF_LOG_ERROR("RendererAPI::None is not currently implemented!");
			return nullptr;
		case RendererAPI::OpenGL:
			//result.reset(static_cast<Shader *>(new OpenGLShader(filepath)));
			//return result;
			return static_cast<Shader*>(new OpenGLShader(filepath));
		}
		DF_LOG_ERROR("Unsupported RendererAPI received!");
		return nullptr;
	}


	Shader * Shader::Create(const char* vert, const char* frag) {
		std::shared_ptr<Shader> result;
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			DF_LOG_ERROR("RendererAPI::None is not currently implemented!");
			return nullptr;
		case RendererAPI::OpenGL:
			//result.reset(static_cast<Shader*>(new OpenGLShader(vert, frag)));
			//return result;
			return static_cast<Shader*>(new OpenGLShader(vert, frag));
		}
		DF_LOG_ERROR("Unsupported RendererAPI received!");
		return nullptr;
	}
}
