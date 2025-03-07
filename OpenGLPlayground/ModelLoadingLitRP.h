#pragma once

#include <memory>

#include "RenderingPipeline.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "LightSystem.h"

namespace Playground
{

#define MAX_LIGHTS_NUMBER 10

class ModelLoadingLitRP : public RenderingPipeline
{
public:
    virtual void Init() override;
    virtual void Draw(const std::unique_ptr<Window> &window, const std::unique_ptr<Camera> &camera) override;
    virtual void Clear() override;

    void ImGuiMenu() override;

private:
    ShaderProgram _shaderProgram;
    std::unique_ptr<LightSystem> _lightSystem;
    std::shared_ptr<Model> _model;
};

} // namespace Playground
