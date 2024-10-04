#pragma once

namespace CubicEngine {
	class RenderBase {
	public:
		RenderBase() = default;
		virtual ~RenderBase() = default;

		virtual void Render() = 0;
	};
}