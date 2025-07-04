#pragma once
#include "../sdl3_context.hpp"
#include "sdl3_triangle_settings.hpp"

namespace SDL3Triangle {
	static void Init(const SDL3Context& context, const SDL3TriangleSettings& settings);
	static void Draw();
}
