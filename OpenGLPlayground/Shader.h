#pragma once

#include <string>

namespace Playground
{
	class Shader
	{
	public:
		const std::string GetShaderCode(const char* shaderPath) const;
		unsigned int Id() { return _id; }
		void Delete();

	protected:
		unsigned int _id;
	};
}
