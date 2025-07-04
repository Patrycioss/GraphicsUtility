#include <sdl3/sdl3_utility.hpp>
#include <SDL3/SDL_log.h>

namespace SDL3Utility {
	SDL_GPUShader* LoadShader(
		const SDL3Context& context,
		const std::string& shaderName,
		const uint32_t samplerCount,
		const uint32_t uniformBufferCount,
		const uint32_t storageBufferCount,
		const uint32_t storageTextureCount
	) {
		// Auto-detect the shader stage from the file name for convenience
		SDL_GPUShaderStage stage;
		if (SDL_strstr(shaderName.c_str(), ".vert")) {
			stage = SDL_GPU_SHADERSTAGE_VERTEX;
		} else if (SDL_strstr(shaderName.c_str(), ".frag")) {
			stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
		} else {
			SDL_Log("Invalid shader stage!");
			return nullptr;
		}

		std::string fullPath{};
		SDL_GPUShaderFormat backendFormats = SDL_GetGPUShaderFormats(context.gpuDevice);
		SDL_GPUShaderFormat format = SDL_GPU_SHADERFORMAT_INVALID;
		std::string entrypoint = "main";

		if (backendFormats & SDL_GPU_SHADERFORMAT_SPIRV) {
			fullPath = context.resourcesPath + "/" + context.compiledShaderPath + "/SPIRV/" + shaderName + ".spv";
			format = SDL_GPU_SHADERFORMAT_SPIRV;
			entrypoint = "main";
		} else if (backendFormats & SDL_GPU_SHADERFORMAT_MSL) {
			fullPath = context.resourcesPath + "/" + context.compiledShaderPath + "/MSL/" + shaderName + ".msl";
			format = SDL_GPU_SHADERFORMAT_MSL;
			entrypoint = "main0";
		} else if (backendFormats & SDL_GPU_SHADERFORMAT_DXIL) {
			fullPath = context.resourcesPath + "/" + context.compiledShaderPath + "/DXIL/" + shaderName + ".dxil";
			format = SDL_GPU_SHADERFORMAT_DXIL;
			entrypoint = "main";
		} else {
			SDL_Log("%s", "Unrecognized backend shader format!");
			return nullptr;
		}

		size_t codeSize;
		void* code = SDL_LoadFile(fullPath.c_str(), &codeSize);
		if (code == nullptr)
		{
			SDL_Log("Failed to load shader from disk! %s", fullPath);
			return nullptr;
		}

		const SDL_GPUShaderCreateInfo shaderInfo = {
			.code_size = codeSize,
			.code = static_cast<uint8_t*>(code),
			.entrypoint = entrypoint.c_str(),
			.format = format,
			.stage = stage,
			.num_samplers = samplerCount,
			.num_storage_textures = storageTextureCount,
			.num_storage_buffers = storageBufferCount,
			.num_uniform_buffers = uniformBufferCount,
		};
		SDL_GPUShader* shader = SDL_CreateGPUShader(context.gpuDevice, &shaderInfo);
		if (shader == nullptr)
		{
			SDL_Log("Failed to create shader!");
			SDL_free(code);
			return nullptr;
		}

		SDL_free(code);
		return shader;
	}
}
