#pragma once

#include "Drifter/Graphics/Texture.h"

namespace Drifter {
	struct Sprite {
		Ref<Texture2D> texture;
		glm::vec4 textureCoordinates;
		glm::vec4 tint;
	};
}