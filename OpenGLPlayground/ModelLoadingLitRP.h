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
		virtual void Draw(const Window* const window,const Camera* const camera) override;
		virtual void Clear() override;

	private:
		ShaderProgram _shaderProgram;
        std::unique_ptr<LightSystem> _lightSystem;
        std::unique_ptr<Model> _model;
	};

}
