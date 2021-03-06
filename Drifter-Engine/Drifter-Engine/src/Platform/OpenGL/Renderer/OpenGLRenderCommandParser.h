#pragma once

#include "Drifter/Renderer/RenderCommand.h"
#include "Drifter/Core/Base.h"
namespace Drifter {

	class OpenGLRenderCommandParser : public RenderCommandParser
	{
		// Inherited via RenderCommandParser
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4 color) override;
		virtual void Clear() override;
		virtual void DrawIndexedTriangles(const Ref<VertexArray>& vertexArray, uint32_t indexCount) override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
	};
}
