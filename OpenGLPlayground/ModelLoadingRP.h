#pragma once

#include "RenderingPipeline.h"

#include "ShaderProgram.h"
#include "Model.h"

namespace Playground
{

#define MAX_LIGHTS_NUMBER 10

class ModelLoadingRP : public RenderingPipeline
{
public:
    virtual void Init() override;
    virtual void Draw(const std::unique_ptr<Window> &window, const std::unique_ptr<Camera> &camera) override;
    virtual void Clear() override;

private:
    ShaderProgram _shaderProgram;
    std::shared_ptr<Model> _model = nullptr;
};

} // namespace Playground
