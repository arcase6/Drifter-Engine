#pragma once

#include "Drifter/Graphics/Texture.h"

namespace Drifter {
	class Sprite {
	public:
		Ref<Texture2D> Texture;
		//Tiling is xy, Offset is zw
		glm::vec4 TilingAndOffset = glm::vec4(1.0f, 1.0f, 0.0f, 0.0f);
		glm::vec4 Tint = glm::vec4(1.0f);
	};
}