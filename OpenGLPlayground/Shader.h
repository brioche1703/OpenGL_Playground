#pragma once

namespace Playground
{
	class Shader
	{
	public:
		unsigned int Id() { return _id; }
		void Delete();

	protected:
		unsigned int _id;
	};
}
