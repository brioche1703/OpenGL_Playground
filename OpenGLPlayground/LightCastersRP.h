#pragma once

#include "RenderingPipeline.h"

#include "ShaderProgram.h"
#include "VertexArrayObject.h"
#include "Buffer.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"
#include "Material.h"
#include "Texture.h"

namespace Playground
{

#define MAX_LIGHTS_NUMBER 10

class LightCastersRP : public RenderingPipeline
{
public:
    virtual void Init() override;
    virtual void Draw(const std::unique_ptr<Window> &window, const std::unique_ptr<Camera> &camera) override;
    virtual void Clear() override;

private:
    ShaderProgram _shaderProgram;
    ShaderProgram _lightCubeShaderProgram;
    VertexArrayObject _VAO, _VAOLight;
    Buffer _VBO;

    DirectionalLight _directionalLight;
    std::vector<PointLight> _pointLights;
    SpotLight _spotLight;

    Material _material;

    Texture _textureContainer = Texture("images/container2.png", GL_TEXTURE_2D, true);
    Texture _textureContainerSpecular = Texture("images/container2_specular.png", GL_TEXTURE_2D, true);
    Texture _textureContainerEmissive = Texture("images/matrix2.png", GL_TEXTURE_2D, true);
};

} // namespace Playground
