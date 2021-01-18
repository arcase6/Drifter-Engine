#pragma once

#include <unordered_map>
#include "Drifter/Graphics/Sprite.h"
namespace Drifter
{
	class Tilemap {
	public:
		Sprite defaultSprite;

		Tilemap(const char* tileData, uint32_t width, std::unordered_map<char, Sprite> tileLookup = std::unordered_map<char, Sprite>()) :
		m_TileData(tileData),  m_Width(width), m_TileLookup(tileLookup)
		{

		}

		void SetRule(char tile, Sprite mapping) {
			m_TileLookup[tile] = mapping;
		}

		uint32_t GetWidth() { return m_Width; }
		uint32_t GetHeight() { return m_TileData.length() / m_Width; }
		Sprite& GetTile(int x, int y);

		void Draw(float z = 0);

	private:
		std::string m_TileData;
		uint32_t m_Width;
		std::unordered_map<char, Sprite> m_TileLookup = std::unordered_map<char, Sprite>();

		glm::vec2 m_Size{ 1.0f };
	};
}