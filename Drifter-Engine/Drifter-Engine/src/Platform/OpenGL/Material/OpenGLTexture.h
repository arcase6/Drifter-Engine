#pragma once
#include "Drifter/Renderer/Material/Texture.h"
namespace Drifter {
	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& filePath);
		virtual ~OpenGLTexture2D();

		// Inherited via Texture2D
		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }
		virtual void Bind(uint32_t slot) const override;

	private:
		uint32_t m_Width, m_Height, m_RendererID;
	};
}

