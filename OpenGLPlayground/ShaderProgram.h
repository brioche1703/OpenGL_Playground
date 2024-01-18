#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string>

namespace Playground
{
class Shader;

class ShaderProgram
{
public:
    ShaderProgram();

    unsigned int GetId() const { return _id; }

    void AttachShader(Shader shader);
    void AttachShader(std::vector<Shader> shaders);
    int GetUniformLocation(const std::string &name) const;
    void LinkProgram();
    void Use();
    void Delete();

    template <typename F, typename... V>
    void SetUniformLocation(const F &fnc, std::string name, const V &...values) const
    {
        fnc(GetUniformLocation(name), values...);
    }

private:
    unsigned int _id;
};
} // namespace Playground
