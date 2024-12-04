#pragma once

namespace CubicEngine {
	namespace Core {
		class EngineCore;
	}

	class RenderBase abstract {
	protected:
		RenderBase() = default;
		virtual ~RenderBase() = default;

	public:
		virtual void Render() = 0;
	};
}
