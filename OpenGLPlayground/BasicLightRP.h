#pragma once

#include "RenderingPipeline.h"

#include "ShaderProgram.h"
#include "VertexArrayObject.h"
#include "Buffer.h"
#include "PointLight.h"
#include "Material.h"

namespace Playground
{
class BasicLightRP : public RenderingPipeline
{
public:
    virtual void Init() override;
    virtual void Draw(const Window *const window, const Camera *const camera) override;
    virtual void Clear() override;

private:
    ShaderProgram _shaderProgram;
    ShaderProgram _lightCubeShaderProgram;
    VertexArrayObject _VAO, _VAOLight;
    Buffer _VBO;

    PointLight light;
    Material material;
};

} // namespace Playground
