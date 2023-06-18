#pragma once

#include <vector>

namespace Playground
{
	class Shader;

	class ShaderProgram
	{
	public:
		ShaderProgram();
		void AttachShader(Shader shader);
		void AttachShader(std::vector<Shader> shaders);
		void LinkProgram();
		void Use();
		void Delete();

	private:
		unsigned int _id;
	};
}
