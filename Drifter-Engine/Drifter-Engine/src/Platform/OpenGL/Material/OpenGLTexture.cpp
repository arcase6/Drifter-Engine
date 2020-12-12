#include "Drifter/Core/dfpch.h"

#include "OpenGLTexture.h"
#include "stb_image.h"
#include "glad/glad.h"

namespace Drifter {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& filePath)
	{
		//load in the image using stb_image
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
		DF_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = GL_RGB8, imageFormat = GL_RGB;

		if (channels == 4) {
			internalFormat = GL_RGBA8;
			imageFormat = GL_RGBA;
		}
		


		//upload the texture to opengl
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, width, height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, imageFormat, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}
	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}
}