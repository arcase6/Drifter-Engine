#include "OpenGLRenderCommandParser.h"

#include "glad/glad.h"
namespace Drifter {
	void OpenGLRenderCommandParser::SetClearColor(const glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderCommandParser::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderCommandParser::DrawIndexedTriangles(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);

	}
}