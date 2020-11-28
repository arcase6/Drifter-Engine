#pragma once
#include <glm/glm.hpp>
#include "VertexArray.h"
namespace Drifter {

	class RenderCommandParser
	{
	public:
		virtual void SetClearColor(const glm::vec4 color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexedTriangles(const std::shared_ptr<VertexArray>& vertexArray) = 0;
	};

	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4 color) {
			s_CommandParser->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_CommandParser->Clear();
		}

		inline static void DrawIndexedTriangles(const std::shared_ptr<VertexArray>& vertexArray) {
			s_CommandParser->DrawIndexedTriangles(vertexArray);
		}

	private:
		static RenderCommandParser* s_CommandParser;
	};
}

