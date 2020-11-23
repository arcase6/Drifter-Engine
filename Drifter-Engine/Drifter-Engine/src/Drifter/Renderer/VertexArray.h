#pragma once

#include <memory>
#include "Drifter/Renderer/Buffer.h"

namespace Drifter {
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		void AddVertexBuffer(VertexBuffer* vertexBuffer) { 
			auto ptr = std::shared_ptr<VertexBuffer>(vertexBuffer);
			AddVertexBuffer(ptr);
		}
		void SetIndexBuffer(IndexBuffer* indexBuffer) {
			auto ptr = std::shared_ptr<IndexBuffer>(indexBuffer);
			SetIndexBuffer(ptr);
		}

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer> indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static VertexArray* Create();

		static VertexArray* Create(std::vector<float> verts, std::vector<uint32_t> indices, BufferLayout layout)
		{
			VertexArray* array = VertexArray::Create();
			array->Bind();

			array->AddVertexBuffer(
				VertexBuffer::Create(&verts[0], verts.size() * sizeof(float), layout)
			);
			array->SetIndexBuffer(
				IndexBuffer::Create(&indices[0], indices.size())
			);

			return array;
		}
	};

}