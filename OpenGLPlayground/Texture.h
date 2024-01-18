#pragma once

#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Playground
{
class Texture
{
public:
    Texture(const std::string &sourcePath, GLenum target = GL_TEXTURE_2D, bool flipY = false, int wrapping = GL_REPEAT,
            const std::string &type = "undefined");

    unsigned int GetID() const { return _id; }
    std::string GetType() const { return _type; }
    std::string GetPath() const { return _path; }

    void Activate(GLenum target) const;
    void Bind() const;

private:
    unsigned int _id;
    std::string _type;
    std::string _path;

    GLenum _target;
    int _width;
    int _height;
    int _nrChannels;
};
} // namespace Playground
