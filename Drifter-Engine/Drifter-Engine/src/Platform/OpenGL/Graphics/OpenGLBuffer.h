#pragma once

#include <Drifter/Graphics/Buffer.h>
namespace Drifter {
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size, const BufferLayout& layout);
		OpenGLVertexBuffer(float* vertices, uint32_t size, const BufferLayout& layout);
		
		// Inherited via VertexBuffer
		virtual ~OpenGLVertexBuffer() override;
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
		
		virtual void SetData(const void* vertices, uint32_t zie, uint32_t offset) override;

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;

	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		// Inherited via IndexBuffer
		virtual ~OpenGLIndexBuffer() override;
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual uint32_t GetCount() const override { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}