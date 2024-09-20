#pragma once

#include "../CubicEngine.h"

namespace CubicEngine {
	namespace Rendering {
		class RenderBase {
		public:
			RenderBase() = default;
			virtual ~RenderBase() = default;

			virtual void Render() = 0;
		};
	}
}