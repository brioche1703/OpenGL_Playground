#include "Texture.h"

#include <stbi/stb_image.h>
#include <iostream>

namespace Playground
{
	Texture::Texture(const std::string& sourcePath, GLenum target, bool flipY, int wrapping)
		:
		_target(target)
	{
		glGenTextures(1, &_id);
		glBindTexture(_target, _id);
		glTexParameteri(_target, GL_TEXTURE_WRAP_S, wrapping);
		glTexParameteri(_target, GL_TEXTURE_WRAP_T, wrapping);
		glTexParameteri(_target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(flipY);  
		unsigned char* data = stbi_load(sourcePath.c_str(), &_width, &_height, &_nrChannels, 0);
		if (data)
		{
			GLenum format = sourcePath.find(".png") != std::string::npos ? GL_RGBA : GL_RGB;
			glTexImage2D(_target, 0, GL_RGB, _width, _height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(_target);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}
	void Texture::Activate(GLenum target) const
	{
		glActiveTexture(target);
	}
	void Texture::Bind() const
	{
		glBindTexture(_target, _id);
	}
}
