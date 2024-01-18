#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Playground
{
class Buffer
{
public:
    Buffer();
    void Bind(GLenum target);
    void Data(GLenum target, GLsizeiptr size, const GLvoid *data, GLenum usage);
    void Delete();

private:
    unsigned int _id;
};

} // namespace Playground
