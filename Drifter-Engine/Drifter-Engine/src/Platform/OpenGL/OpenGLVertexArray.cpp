#include "Drifter/Core/dfpch.h"

#include "OpenGLVertexArray.h"
#include "glad/glad.h"

namespace Drifter {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case Drifter::ShaderDataType::Float:    return GL_FLOAT;
		case Drifter::ShaderDataType::Float2:   return GL_FLOAT;
		case Drifter::ShaderDataType::Float3:   return GL_FLOAT;
		case Drifter::ShaderDataType::Float4:   return GL_FLOAT;
		case Drifter::ShaderDataType::Mat3:     return GL_FLOAT;
		case Drifter::ShaderDataType::Mat4:     return GL_FLOAT;
		case Drifter::ShaderDataType::Int:      return GL_INT;
		case Drifter::ShaderDataType::Int2:     return GL_INT;
		case Drifter::ShaderDataType::Int3:     return GL_INT;
		case Drifter::ShaderDataType::Int4:     return GL_INT;
		case Drifter::ShaderDataType::Bool:     return GL_BOOL;
		}

		DF_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}
	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}
	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer> vertexBuffer)
	{
		DF_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer Layout not set!");
		
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();

		auto layout = vertexBuffer->GetLayout();
		int index = 0;
		for (auto& bufferElement : layout) {
			glEnableVertexAttribArray(index);
			uint64_t offset = static_cast<uint64_t>(bufferElement.Offset);
			glVertexAttribPointer(
				index,
				bufferElement.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(bufferElement.Type),
				bufferElement.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)offset
			);
			index++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer> indexBuffer)
	{

		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;


	}
}