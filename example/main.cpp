#include <iostream>
#include <graphics_utility.hpp>
#include <memory>
#include <sdl3/sdl3_graphics_utility.hpp>
#include <SDL3/SDL.h>

int main() {
	bool done = false;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_GPUDevice* gpuDevice = SDL_CreateGPUDevice(
		SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL,
		false,
		nullptr
	);

	if (gpuDevice == nullptr) {
		SDL_Log("GPUCreateDevice failed");
		return 1;
	}

	constexpr SDL_WindowFlags flags = 0;

	SDL_Window* window = SDL_CreateWindow(
		"Graphics Util Test App",
		800,
		600,
		flags
	);

	if (window == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	if (!SDL_ClaimWindowForGPUDevice(gpuDevice, window)) {
		SDL_Log("GPUClaimWindow failed");
		return 1;
	}

	std::unique_ptr<GraphicsUtility> graphicsUtility = std::make_unique<SDL3GraphicsUtility>(gpuDevice, window);

	while (!done) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				done = true;
			}
		}

		graphicsUtility->startRendering();
		graphicsUtility->clear(Colour{255,0,0,255});
		graphicsUtility->stopRendering();
	}

	SDL_ReleaseWindowFromGPUDevice(gpuDevice, window);
	SDL_DestroyWindow(window);
	SDL_DestroyGPUDevice(gpuDevice);
	SDL_Quit();
	return 0;
}
