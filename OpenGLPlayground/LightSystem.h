#pragma once

#include <vector>

#include "DirectionalLight.h"
#include "PointLight.h"
#include "VertexArrayObject.h"
#include "Buffer.h"
#include "ShaderProgram.h"

namespace Playground
{
	class SpotLight;

	class LightSystem
	{
	public:
		LightSystem(std::vector<PointLight> pointLights);

		void Init();
		void SetUniforms(const ShaderProgram& shaderProgram, const glm::mat4& view, const glm::mat4& proj); 
		void DrawLightsObjects(const glm::mat4& view, const glm::mat4& proj);

	private:
		DirectionalLight _directionalLight;
		std::vector<PointLight> _pointLights;
		std::vector<SpotLight> _spotLights;

		ShaderProgram _lightCubeShaderProgram;
		VertexArrayObject _VAOLight;
		Buffer _VBO;
	};
}

