#pragma once

#include "Drifter/Camera/Camera.h"
#include "Drifter/Graphics/Texture.h"
#include "Drifter/Transform.h"
#include "glm/glm.hpp"

namespace Drifter {
	class Renderer2D
	{
	public:
		static void Init();
	public:
		static void Shutdown();

		static void BeginScene(const Camera& camera);
		static void EndScene();
		static void FlushBatch();
		
		//primative draw methods

		static void DrawQuad(const RectTransform& transform, const glm::vec4& color);
		static void DrawQuad(const RectTransform& transform, const glm::vec4& tint, const Ref<const Texture> texture);


		static void OnWindowResize(uint32_t width, uint32_t height);
	};

}