#pragma once
#include "Drifter/Graphics/VertexArray.h"

namespace Drifter {
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() override;

		// Inherited via VertexArray
		virtual void Bind() override;
		virtual void Unbind() override;
		
		virtual void AddVertexBuffer(const Ref<VertexBuffer> vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer> indexBuffer) override;
		
		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override
		{
			return m_VertexBuffers;
		}
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override
		{
			return m_IndexBuffer;
		}
	private:
		uint32_t m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;
		Ref<IndexBuffer> m_IndexBuffer;
	};
}

