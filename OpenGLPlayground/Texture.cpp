#include "Texture.h"

#include <stbi/stb_image.h>
#include <iostream>

namespace Playground
{
Texture::Texture(const std::string &sourcePath, GLenum target, bool flipY, int wrapping, const std::string &type)
    : _type(type)
    , _path(sourcePath)
    , _target(target)
{
    glGenTextures(1, &_id);
    int width, height, nrComponents;

    stbi_set_flip_vertically_on_load(flipY);

    unsigned char *data = stbi_load(sourcePath.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
        {
            format = GL_RED;
        }
        else if (nrComponents == 3)
        {
            format = GL_RGB;
        }
        else
        {
            format = GL_RGBA;
        }

        glBindTexture(target, _id);
        glTexImage2D(target, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(target);

        glTexParameteri(target, wrapping, wrapping);
        glTexParameteri(target, wrapping, wrapping);
        glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << sourcePath << std::endl;
        stbi_image_free(data);
    }
}

void Texture::Activate(GLenum target) const
{
    glActiveTexture(target);
}
void Texture::Bind() const
{
    glBindTexture(_target, _id);
}
void Texture::Delete() const
{
    glDeleteTextures(1, &_id);
}
} // namespace Playground
