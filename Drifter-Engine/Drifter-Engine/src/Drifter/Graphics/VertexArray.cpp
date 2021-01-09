#include "dfpch.h"
#include "Drifter/Graphics/VertexArray.h"

#include "Drifter/Renderer/Renderer.h"
#include "Platform/OpenGL/Graphics/OpenGLVertexArray.h"


namespace Drifter {

	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::None: 
			DF_LOG_ERROR("RendererAPI is not supported");
			return nullptr;
		case RendererAPI::OpenGL:
			return std::shared_ptr<VertexArray>(new OpenGLVertexArray());
		}
		DF_LOG_ERROR("RendererAPI is not supported");
			return nullptr;
	}
}