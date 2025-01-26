#pragma once

#include <vector>

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "VertexArrayObject.h"
#include "Buffer.h"
#include "ShaderProgram.h"

namespace Playground
{
class LightSystem
{
public:
    LightSystem(std::vector<std::shared_ptr<PointLight>> pointLights);

    void Init();
    void SetUniforms(const ShaderProgram &shaderProgram, const glm::mat4 &view, const glm::mat4 &proj);
    void DrawLightsObjects(const glm::mat4 &view, const glm::mat4 &proj);

private:
    std::shared_ptr<DirectionalLight> _directionalLight;
    std::vector<std::shared_ptr<PointLight>> _pointLights;
    std::vector<std::shared_ptr<SpotLight>> _spotLights;

    ShaderProgram _lightCubeShaderProgram;
    VertexArrayObject _VAOLight;
    Buffer _VBO;
};
} // namespace Playground
