#pragma once

namespace Playground
{
	class Window;
	class Camera;

	class RenderingPipeline
	{
	public:
		virtual void Init() = 0;
		virtual void Draw(Window* window, Camera* camera) = 0;
		virtual void Clear() = 0;
	};
}
