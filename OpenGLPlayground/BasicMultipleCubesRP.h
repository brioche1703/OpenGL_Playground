#pragma once

#include "RenderingPipeline.h"

#include "ShaderProgram.h"
#include "VertexArrayObject.h"
#include "Buffer.h"
#include "Texture.h"

namespace Playground
{

	class BasicMultipleCubesRP : public RenderingPipeline
	{
	public:
		virtual void Init() override;
		virtual void Draw(const Window* const window, const Camera* const camera) override;
		virtual void Clear() override;

	private:
		ShaderProgram _shaderProgram;
		VertexArrayObject _VAO;
		Buffer _VBO;
		Texture _texture1 = Texture("images/container.jpg", GL_TEXTURE_2D, true);
		Texture _texture2 = Texture("images/smiley.png", GL_TEXTURE_2D, true);
	};
}
