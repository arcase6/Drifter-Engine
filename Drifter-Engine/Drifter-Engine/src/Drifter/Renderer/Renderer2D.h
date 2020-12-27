#pragma once

#include "glm/glm.hpp"
#include "Drifter/Renderer/Cameras/Camera.h"
#include "Drifter/Transform.h"
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

		static void DrawQuad(const RectTransform& transform, const glm::vec4 color);
	};

}