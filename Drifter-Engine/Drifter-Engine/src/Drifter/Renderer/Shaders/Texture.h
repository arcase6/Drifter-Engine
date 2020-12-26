#pragma once

#include "Core.h"
#include <string>
#include "glm/glm.hpp"

namespace Drifter {
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot) const = 0;
	};
	
	class Texture2D : public Texture 
	{
	public:
		virtual ~Texture2D() = default;

		static Ref<Texture2D> Create(const std::string& filepath);
		static Ref<Texture2D> Create(const glm::vec4& flatColor, int width, int height);
	};
}
