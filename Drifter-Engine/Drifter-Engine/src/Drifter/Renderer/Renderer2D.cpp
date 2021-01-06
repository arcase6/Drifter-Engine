#include "dfpch.h"
#include "Drifter/Renderer/Renderer2D.h"
#include "Drifter/Renderer/Renderer.h"
#include "Drifter/Renderer/RenderCommand.h"

#include "Platform/OpenGL/Renderer/Shaders/OpenGLShader.h"

#include "glm/gtc/matrix_transform.hpp"
#include "DebugUtil/Instrumentation.h"
namespace Drifter {

	struct QuadVertex {
		glm::vec4 Position;
		glm::vec2 UV;
		glm::vec4 Color;
		float Tex;
	};

	struct RendererData2D {
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVerts = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;

		glm::mat4 ViewProjectionMatrix = glm::mat4(1.0f);
		Ref<VertexBuffer> BatchVertexBuffer = nullptr;
		Ref<VertexArray> BatchVertexArray = nullptr;
		Ref<Shader> SpriteShader = nullptr;
		Ref<Texture2D> DefaultTexture = nullptr;

		//runtimeData
		QuadVertex*  QuadVertexDataBuffer = nullptr;
		QuadVertex* QuadVertexDataBufferOffset = nullptr;
		uint32_t IndexCount = 0;
		
		RendererData2D() {
			QuadVertexDataBuffer = new QuadVertex[MaxVerts];
		}

		~RendererData2D() {
			delete[] QuadVertexDataBuffer;
		}
	};

	static RendererData2D s_Data;


	void InitBatchIndexArray() {
		Ref<uint32_t[]> indices(new uint32_t[s_Data.MaxIndices]);

		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6) {
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 1;
			indices[i + 5] = offset + 3;

			offset += 4;
		}

		s_Data.BatchVertexArray->SetIndexBuffer(IndexBuffer::Create(indices, s_Data.MaxIndices));
	}

	void InitBatchVertexArray() {
		Drifter::BufferLayout layout = {
			{ Drifter::ShaderDataType::Float4, "a_Position" },
			{ Drifter::ShaderDataType::Float2, "a_UV" },
			{ Drifter::ShaderDataType::Float4, "a_Tint" },
			{ Drifter::ShaderDataType::Float, "a_Tex" }
		};
		s_Data.BatchVertexBuffer = VertexBuffer::Create(s_Data.MaxVerts, layout);
		s_Data.BatchVertexArray->AddVertexBuffer(s_Data.BatchVertexBuffer);
	}

	void Renderer2D::Init() {
		PROFILE_RENDERER_FUNCTION();
		
		s_Data.SpriteShader = Renderer::GetShaderLibrary().FindShader("QuadBatchShader");
		s_Data.DefaultTexture = Texture2D::Create(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1, 1);
		s_Data.BatchVertexArray = VertexArray::Create();

		InitBatchIndexArray();
		InitBatchVertexArray();
		
	}

	void Renderer2D::Shutdown() {

	}

	void Renderer2D::BeginScene(const Camera& camera)
	{
		PROFILE_RENDERER_FUNCTION();
		s_Data.ViewProjectionMatrix = camera.GetProjectionMatrix() * camera.GetViewMatrix();
		s_Data.SpriteShader->Bind();

		s_Data.QuadVertexDataBufferOffset = s_Data.QuadVertexDataBuffer;
		s_Data.IndexCount = 0;
	}
	void Renderer2D::EndScene()
	{
		PROFILE_RENDERER_FUNCTION();
		FlushBatch();
	}

	void Renderer2D::FlushBatch() {
		uint32_t dataSize = (QuadVertex*)s_Data.QuadVertexDataBufferOffset - (QuadVertex*)s_Data.QuadVertexDataBuffer;
		if (dataSize == 0) {
			return;
		}
		s_Data.BatchVertexBuffer->SetData(s_Data.QuadVertexDataBuffer, dataSize, 0);

		s_Data.DefaultTexture->Bind(0);
		s_Data.SpriteShader->SetMat4("u_ViewProjection", s_Data.ViewProjectionMatrix);

		//s_Data.SpriteShader->SetMat4("u_Model", transform.GetTransformMatrix());
		//s_Data.SpriteShader->SetVec4("u_Tint", tint);

		RenderCommand::DrawIndexedTriangles(s_Data.BatchVertexArray, s_Data.IndexCount);
	
		s_Data.QuadVertexDataBufferOffset = s_Data.QuadVertexDataBuffer;
		s_Data.IndexCount = 0;
	}

	void Renderer2D::OnWindowResize(uint32_t width, uint32_t height) {

	}
	void Renderer2D::DrawQuad(const RectTransform& transform, const glm::vec4& color) {
		Renderer2D::DrawQuad(transform , color, s_Data.DefaultTexture);
	}


	void Renderer2D::DrawQuad(const RectTransform& transform, const glm::vec4& tint, const Ref<const Texture> texture) {
		PROFILE_RENDERER_FUNCTION();
		static const glm::mat4 quad =  glm::mat4(glm::vec4(0.0, 0.0, 0.0, 1.0f), glm::vec4(0.0, -1.0, 0.0, 1.0f), glm::vec4(1.0, 0.0, 0.0, 1.0f), glm::vec4(1.0, -1.0, 0.0, 1.0f));
		static const glm::vec2 uvs[4] = { glm::vec2(0.0f, 1.0f),                 glm::vec2(0.0f, 0.0f),           glm::vec2(1.0f, 1.0f),          glm::vec2(1.0f, 0.0f), };

		glm::mat4 transformedQuad = transform.GetTransformMatrix() * quad;

		if (s_Data.IndexCount + 6 < s_Data.MaxIndices) {
			FlushBatch();
		}

		for (int i = 0; i < 4; i++) {
			//*(s_Data.QuadVertexDataBufferOffset) = QuadVertex();
			s_Data.QuadVertexDataBufferOffset->Position = transformedQuad[i];
			s_Data.QuadVertexDataBufferOffset->UV = uvs[i];
			s_Data.QuadVertexDataBufferOffset->Color = tint;
			s_Data.QuadVertexDataBufferOffset->Tex = 0; //TO-DO add texture
			
			s_Data.QuadVertexDataBufferOffset++;
		}
		s_Data.IndexCount += 6;

	}
}