#include "dfpch.h"

#include "OpenGLTexture.h"
#include "stb_image.h"
#include "glad/glad.h"

#include "glm/glm.hpp"

#include "DebugUtil/Debug.h"

namespace Drifter {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& filePath)
	{
		//load in the image using stb_image
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(filePath.c_str(), &width, &height, &channels, 0);
		DF_ASSERT_LV1(data, "Failed to load image!");
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

	OpenGLTexture2D::OpenGLTexture2D(const glm::vec4& flatColor, int width, int height)
	{
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = GL_RGBA8, imageFormat = GL_RGBA;
		uint8_t color[4];
		color[0] = static_cast<uint8_t>(flatColor.x * 255);
		color[1] = static_cast<uint8_t>(flatColor.y * 255);
		color[2] = static_cast<uint8_t>(flatColor.z * 255);
		color[3] = static_cast<uint8_t>(flatColor.w * 255);

		int dataSize = 4 * width * height;
		auto data = std::make_unique<unsigned char[]>(dataSize);
		for (int pixel = 0; pixel < width * height; pixel++) {
			for (int channel = 0; channel < 4; channel++) {
				int index = pixel * 4 + channel;
				data[index] = color[channel];
			}
		}

		//upload the texture to opengl
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, width, height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, imageFormat, GL_UNSIGNED_BYTE, &data[0]);
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