#include "dfpch.h"

#include "Buffer.h"

#include "Drifter/Renderer/Renderer.h"

#include <Platform/OpenGL/Graphics/OpenGLBuffer.h>

namespace Drifter {

	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size, const BufferLayout& layout)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			DF_LOG_ERROR("RendererAPI::None is not currently implemented!");
			break;
		case RendererAPI::OpenGL:
			return std::shared_ptr<VertexBuffer>(new OpenGLVertexBuffer(size, layout));
		}
		DF_ASSERT_UNREACHABLE_LV1("Unsupported RendererAPI received!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(Ref<float[]> vertices, uint32_t count, const BufferLayout& layout)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:
				DF_LOG_ERROR("RendererAPI::None is not currently implemented!");
				break;
			case RendererAPI::OpenGL:
				return std::shared_ptr<VertexBuffer>(new OpenGLVertexBuffer(vertices.get(), count, layout));
		}
		DF_ASSERT_UNREACHABLE_LV1("Unsupported RendererAPI received!");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, uint32_t count, const BufferLayout& layout)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			DF_LOG_ERROR("RendererAPI::None is not currently implemented!");
			break;
		case RendererAPI::OpenGL:
			return std::shared_ptr<VertexBuffer>(new OpenGLVertexBuffer(vertices, count, layout));
		}
		DF_ASSERT_UNREACHABLE_LV1("Unsupported RendererAPI received!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(Ref<uint32_t[]> indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			DF_LOG_ERROR("RendererAPI::None is not currently implemented!");
			break;
		case RendererAPI::OpenGL:
			return std::shared_ptr<IndexBuffer>(new OpenGLIndexBuffer(indices.get(), count));
		}
		DF_ASSERT_UNREACHABLE_LV1("Unsupported RendererAPI received!");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t * indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			DF_LOG_ERROR("RendererAPI::None is not currently implemented!");
			break;
		case RendererAPI::OpenGL:
			return std::shared_ptr<IndexBuffer>(new OpenGLIndexBuffer(indices, count));
		}
		DF_ASSERT_UNREACHABLE_LV1("Unsupported RendererAPI received!");
		return nullptr;
	}
}