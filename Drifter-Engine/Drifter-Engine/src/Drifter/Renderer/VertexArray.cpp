#include "dfpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"


namespace Drifter {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {
		case RendererAPI::None: 
			DF_LOG_ERROR("RendererAPI is not supported");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexArray();
		}
		DF_LOG_ERROR("RendererAPI is not supported");
			return nullptr;
	}
}