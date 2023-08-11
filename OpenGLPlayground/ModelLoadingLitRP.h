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

	class ModelLoadingLitRP : public RenderingPipeline
	{
	public:
		~ModelLoadingLitRP() { delete _model; _model = nullptr; }
		virtual void Init() override;
		virtual void Draw(Window* window, Camera* camera) override;
		virtual void Clear() override;

	private:
		ShaderProgram _shaderProgram;

		DirectionalLight _directionalLight;
		std::vector<PointLight> _pointLights;
		SpotLight _spotLight;

		Material _material;

		Model* _model = nullptr;
	};

}
