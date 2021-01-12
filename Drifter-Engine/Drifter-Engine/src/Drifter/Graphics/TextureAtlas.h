#pragma once

#include "Drifter/Core/Base.h"
#include "glm/glm.hpp"
#include "Drifter/Graphics/Sprite.h"


namespace Drifter {
	class TextureAtlas
	{
	public:
		virtual ~TextureAtlas() {}

		virtual size_t GetSpriteCount() const= 0;
		virtual const Sprite& GetSprite(int index) const= 0;
	};

	class UniformTextureAtlas : public TextureAtlas
	{
	public:
		UniformTextureAtlas(Ref<Texture2D> texture, glm::ivec2 spriteDim, glm::ivec2 padding = glm::ivec2(0.0))
			: m_Texture(texture),
			m_Dimensions(CalculateSpriteRange(spriteDim, padding))
		{
			if (GetSpriteCount() == 0)
				return;
			m_Sprites = new Sprite[GetSpriteCount()];
			glm::vec2 relativeSize = glm::vec2((float)spriteDim.x / texture->GetWidth(), (float)spriteDim.y /  texture->GetHeight());
			
			glm::vec2 tiling = relativeSize;
			for (size_t y = 0; y < m_Dimensions.y; ++y) {
				int offset = y * m_Dimensions.x;
				for (size_t x = 0; x < m_Dimensions.x; ++x) {
					int index = offset + x;
					m_Sprites[index].Texture = texture;
					glm::vec2 offset{x * relativeSize.x , y * relativeSize.y };
					m_Sprites[index].TilingAndOffset = glm::vec4(tiling, offset);
				}
			}

		}

		~UniformTextureAtlas() { delete[] m_Sprites; }

		virtual size_t GetSpriteCount() const override { return (size_t)(m_Dimensions.x * m_Dimensions.y); }
		glm::ivec2 GetSpriteDimensions() const { return m_Dimensions; }

		virtual const Sprite& GetSprite(int index) const override { return m_Sprites[index]; }
		const Sprite& GetSprite(glm::ivec2 coordinates) const { return m_Sprites[coordinates.y * m_Dimensions.x + coordinates.x]; }

	private:

		glm::ivec2& CalculateSpriteRange(glm::vec2 spriteSize, glm::vec2 padding) {
			glm::vec2 step = spriteSize + padding;
			glm::ivec2 range;
			range.x = (int)(m_Texture->GetWidth() / step.x);
			range.y = (int)(m_Texture->GetHeight() / step.y);

			if (range.x * step.x + spriteSize.x < m_Texture->GetWidth())
				++range.x;
			if (range.y * step.y + spriteSize.y < m_Texture->GetHeight())
				++range.x;
			return range;
		}


	private:
		Ref<Texture2D> m_Texture;
		glm::ivec2 m_Dimensions{ 0, 0 };
		Sprite* m_Sprites = nullptr;
	};
}