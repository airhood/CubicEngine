#pragma once

namespace CubicEngine {
	class RenderBase abstract {
	public:
		RenderBase() = default;
		virtual ~RenderBase() = default;

		virtual void Render() = 0;
	};
}