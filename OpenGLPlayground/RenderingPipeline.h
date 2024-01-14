#pragma once

namespace Playground
{
	class Window;
	class Camera;

	class RenderingPipeline
	{
	public:
        virtual ~RenderingPipeline() = default;
		virtual void Init() = 0;
		virtual void Draw(const Window* const window, const Camera* const camera) = 0;
		virtual void Clear() = 0;
	};
}
