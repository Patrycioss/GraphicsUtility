#pragma once
#include <SDL3/SDL_gpu.h>
#include <string>

#include "sdl3_context.hpp"

namespace SDL3Utility {
	SDL_GPUShader* LoadShader(
		const SDL3Context& context,
		const std::string& shaderName,
		uint32_t samplerCount,
		uint32_t uniformBufferCount,
		uint32_t storageBufferCount,
		uint32_t storageTextureCount
	);
}
