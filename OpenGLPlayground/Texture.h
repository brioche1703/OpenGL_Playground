#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Playground
{
	class Texture
	{
	public:
		Texture(const std::string& sourcePath, GLenum target = GL_TEXTURE_2D, bool flipY = false, int wrapping = GL_REPEAT);
		void Activate(GLenum target) const;
		void Bind() const;

	private:
		unsigned int _id;
		GLenum _target;
		int _width;
		int _height;
		int _nrChannels;
	};
}
