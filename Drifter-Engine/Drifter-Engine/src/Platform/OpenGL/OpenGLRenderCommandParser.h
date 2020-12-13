#pragma once

#include "Drifter/Renderer/RenderCommand.h"
namespace Drifter {

	class OpenGLRenderCommandParser : public RenderCommandParser
	{
		// Inherited via RenderCommandParser
		virtual void Init() override;
		virtual void SetClearColor(const glm::vec4 color) override;
		virtual void Clear() override;
		virtual void DrawIndexedTriangles(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}
