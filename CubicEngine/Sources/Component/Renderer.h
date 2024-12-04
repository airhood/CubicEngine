#pragma once

namespace CubicEngine {
	class Renderer abstract {
	protected:
		Renderer() = default;
		virtual ~Renderer() = default;

	public:
		virtual void Render() = 0;

		void SetRenderOrder(int value);

		int GetRenderOrder() const;

	private:
		int renderOrder = 0;
	};
}