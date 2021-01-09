#include "dfpch.h"
#include "Texture.h"
#include "Drifter/Core/Base.h"

#include "Drifter/Renderer/Renderer.h"
#include "Platform/OpenGL/Graphics/OpenGLTexture.h"

namespace Drifter
{
	Ref<Texture2D> Texture2D::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			DF_LOG_ERROR("RendererAPI::None is not currently implemented!");
			return nullptr;
		case RendererAPI::OpenGL:
			return CreateRef<OpenGLTexture2D>(filepath);

		}
		DF_LOG_ERROR("Unsupported RendererAPI received!");
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(const glm::vec4& flatColor, int width, int height) {
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			DF_LOG_ERROR("RendererAPI::None is not currently implemented!");
			return nullptr;
		case RendererAPI::OpenGL:
			return CreateRef<OpenGLTexture2D>(flatColor, width, height);

		}
		DF_LOG_ERROR("Unsupported RendererAPI received!");
		return nullptr;
	}

}