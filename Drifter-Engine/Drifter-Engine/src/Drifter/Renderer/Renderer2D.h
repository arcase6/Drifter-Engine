#pragma once

#include "Drifter/Camera/Camera.h"
#include "Drifter/Graphics/Texture.h"
#include "Drifter/Graphics/Sprite.h"
#include "Drifter/Transform.h"
#include "glm/glm.hpp"

#include "Drifter/Renderer/RendererStatistics.h"

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
		static void DrawQuad(const RectTransform& transform, const glm::vec4& tint, const Ref<Texture2D> texture, const glm::vec4& textureCoordinates = glm::vec4(1,1, 0, 0));
		static void DrawSprite(const RectTransform& transform, const Sprite& sprite);


		static void OnWindowResize(uint32_t width, uint32_t height);

		static Renderer2DStatistics& GetStats(){static Renderer2DStatistics stats; return stats;}
	};

}