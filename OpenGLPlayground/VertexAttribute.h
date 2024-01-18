#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Playground
{
class VertexAttribute
{
  public:
    VertexAttribute();

    void Enable(GLuint index);

    template <typename F, typename... V> void SetAttributePointer(const F &fnc, const V &...values)
    {
        fnc(values...);
    }
};
} // namespace Playground
