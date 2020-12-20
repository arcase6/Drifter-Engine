#include "dfpch.h"
#include "Texture.h"
#include "Core.h"

#include "Drifter/Renderer/Renderer.h"
#include "Platform/OpenGL/Material/OpenGLTexture.h"

namespace Drifter
{
	Ref<Texture2D> Texture2D::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::None:
			DF_LOG_ERROR("RendererAPI::None is not currently implemented!");
			return nullptr;
		case RendererAPI::OpenGL:
			return std::make_shared<OpenGLTexture2D>(filepath);

		}
		DF_LOG_ERROR("Unsupported RendererAPI received!");
		return nullptr;
	}
}