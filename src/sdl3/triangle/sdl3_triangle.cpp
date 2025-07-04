#include <sdl3/triangle/sdl3_triangle.hpp>
#include <sdl3/sdl3_utility.hpp>

namespace SDL3Triangle {
	void Init(const SDL3Context& context, const SDL3TriangleSettings& settings) {
		const SDL_GPUShader* vertexShader = SDL3Utility::LoadShader(
			context,
			settings.vertexShaderPath,
			0,
			0,
			0,
			0
		);
		
		if (vertexShader == nullptr) {
			SDL_Log("Failed to create vertex shader!");
			return;
		}
	}

	void Draw() {
	}
}
