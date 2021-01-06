#include "OpenGLRenderCommandParser.h"

#include "glad/glad.h"
namespace Drifter {
	void OpenGLRenderCommandParser::Init()
	{
		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void OpenGLRenderCommandParser::SetClearColor(const glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderCommandParser::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderCommandParser::DrawIndexedTriangles(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount)
	{
		vertexArray->Bind();
		if (indexCount == 0)
			indexCount = vertexArray->GetIndexBuffer()->GetCount();

		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
	}

	void OpenGLRenderCommandParser::SetViewport(uint32_t x, uint32_t y,uint32_t width, uint32_t height) {
		glViewport(x, y, width, height);
	}

}