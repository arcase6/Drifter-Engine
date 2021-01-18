#include "dfpch.h"
#include "Tilemap.h"
#include "Drifter/Renderer/Renderer2D.h"

namespace Drifter {
	inline Sprite& Tilemap::GetTile(int x, int y) {
		char tile = m_TileData[y * m_Width + x];
		if (m_TileLookup.find(tile) == m_TileLookup.end())
			return defaultSprite;
		return m_TileLookup[tile];
	}

	void Tilemap::Draw(float z) {
		uint32_t width = GetWidth();
		uint32_t height = GetHeight();
		RectTransform transform({ 0,0 }, m_Size);
		for (int y = 0; y < height; ++y) {
			float yPos = m_Size.y * (height - y); //invert y
			for (int x = 0; x < width; ++x) {
				transform.SetPosition({ m_Size.x * x, yPos , z });
				auto& sprite = GetTile( x,y );
				if(sprite.Texture.get() != nullptr)
					Renderer2D::DrawSprite(transform, sprite);
			}
		}
	}
}