#pragma once

#include "RenderingPipeline.h"

#include "ShaderProgram.h"
#include "Model.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "Material.h"

namespace Playground
{

#define MAX_LIGHTS_NUMBER 10

	class LightSystem;
	class ModelLoadingLitRP : public RenderingPipeline
	{
	public:
		~ModelLoadingLitRP();
		virtual void Init() override;
		virtual void Draw(Window* window, Camera* camera) override;
		virtual void Clear() override;

	private:
		ShaderProgram _shaderProgram;
		LightSystem* _lightSystem;
		Model* _model = nullptr;
	};

}
