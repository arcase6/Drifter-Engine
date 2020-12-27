#pragma once

#include "glm/glm.hpp"
#include "Drifter/Renderer/Cameras/Camera.h"
namespace Drifter {
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera);
		static void EndScene();
		static void OnWindowResize(uint32_t width, uint32_t height);

		//primative draw methods

		static void DrawQuad(const glm::vec2& topLeft, const glm::vec2& size, float rotation, const glm::vec4 color);
		static void DrawQuad(const glm::vec3& topLeft, const glm::vec2& size, float rotation, const glm::vec4 color);
	};

}