#pragma once

namespace CubicEngine::RenderUnit {
	constexpr unsigned int ALBEDO         = 0;
	constexpr unsigned int NORMAL         = 1;
	constexpr unsigned int METALLIC       = 2;
	constexpr unsigned int ROUGHNESS      = 3;
	constexpr unsigned int AO             = 4;
	constexpr unsigned int EMISSION       = 5;

	constexpr unsigned int SPRITE         = 6;

	constexpr unsigned int SHADOW_MAP     = 7;
	constexpr unsigned int SHADOW_CUBE    = 8;
	constexpr unsigned int GBUFFER_DEPTH  = 9;
	constexpr unsigned int GBUFFER_NORMAL = 10;

	constexpr unsigned int IRRADIANCE_MAP = 11;
	constexpr unsigned int PREFILTER_MAP  = 12;
	constexpr unsigned int BRDF_LUT       = 13;

	constexpr unsigned int POSTFX_0       = 14;
	constexpr unsigned int POSTFX_1       = 15;
}