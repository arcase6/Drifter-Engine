#include "Drifter/Core/dfpch.h"

#include "Buffer.h"

#include "Renderer.h"

#include <Platform/OpenGL/OpenGLBuffer.h>

namespace Drifter {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size, const BufferLayout& layout)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:
				DF_LOG_ERROR("RendererAPI::None is not currently implemented!");
				return nullptr;
			case RendererAPI::OpenGL:
				return static_cast<VertexBuffer *>(new OpenGLVertexBuffer(vertices, size, layout));
		}
		DF_LOG_ERROR("Unsupported RendererAPI received!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			DF_LOG_ERROR("RendererAPI::None is not currently implemented!");
			return nullptr;
		case RendererAPI::OpenGL:
			return static_cast<IndexBuffer *>(new OpenGLIndexBuffer(indices, count));
		}
		DF_LOG_ERROR("Unsupported RendererAPI received!");
		return nullptr;
	}
}