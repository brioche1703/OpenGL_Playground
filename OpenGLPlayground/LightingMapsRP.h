#pragma once

#include "RenderingPipeline.h"

#include "ShaderProgram.h"
#include "VertexArrayObject.h"
#include "Buffer.h"
#include "PointLight.h"
#include "Material.h"
#include "Texture.h"

namespace Playground
{
	class LightingMaps : public RenderingPipeline
	{
	public:
		virtual void Init() override;
		virtual void Draw(Window* window, Camera* camera) override;
		virtual void Clear() override;

	private:
		ShaderProgram _shaderProgram;
		ShaderProgram _lightCubeShaderProgram;
		VertexArrayObject _VAO, _VAOLight;
		Buffer _VBO;

		PointLight light;
		Material material;

		Texture _textureContainer = Texture("images/container2.png", GL_TEXTURE_2D, true);
		Texture _textureContainerSpecular = Texture("images/container2_specular.png", GL_TEXTURE_2D, true);
	};

}
