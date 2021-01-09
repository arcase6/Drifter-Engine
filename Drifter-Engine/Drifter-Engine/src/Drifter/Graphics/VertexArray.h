#pragma once

#include "Drifter/Graphics/GraphicsInterfaces.h"
#include <memory>
#include "Drifter/Graphics/Buffer.h"

namespace Drifter {
	class VertexArray : public IBindable
	{
	public:
		virtual ~VertexArray() {}

		void AddVertexBuffer(VertexBuffer* vertexBuffer) { 
			auto ptr = Ref<VertexBuffer>(vertexBuffer);
			AddVertexBuffer(ptr);
		}
		void SetIndexBuffer(IndexBuffer* indexBuffer) {
			auto ptr = Ref<IndexBuffer>(indexBuffer);
			SetIndexBuffer(ptr);
		}

		virtual void AddVertexBuffer(const Ref<VertexBuffer> vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<IndexBuffer> indexBuffer) = 0;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

		static Ref<VertexArray> Create();

		template<typename T>
		static Ref<VertexArray> Create(std::vector<T> verts, std::vector<uint32_t> indices, BufferLayout layout)
		{
			Ref<VertexArray> array = VertexArray::Create();
			array->Bind();

			array->AddVertexBuffer(
				VertexBuffer::Create(&verts[0], static_cast<uint32_t>(verts.size()), layout)
			);
			array->SetIndexBuffer(
				IndexBuffer::Create(&indices[0], static_cast<uint32_t>(indices.size()))
			);

			return array;
		}

		template<typename T>
		static Ref<VertexArray> Create(Ref<T[]> verts, Ref<uint32_t[]> indices, uint32_t vertexCount, uint32_t IndexCount, BufferLayout layout)
		{
			Ref<VertexArray> array = VertexArray::Create();
			array->Bind();

			array->AddVertexBuffer(
				VertexBuffer::Create(verts.get(), vertexCount, layout)
			);
			array->SetIndexBuffer(
				IndexBuffer::Create(indices.get(), IndexCount)
			);

			return array;
		}
	};

}