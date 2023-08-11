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
		~ModelLoadingRP() { delete _model; }
		virtual void Init() override;
		virtual void Draw(Window* window, Camera* camera) override;
		virtual void Clear() override;

	private:
		ShaderProgram _shaderProgram;
		Model* _model;
	};

}
