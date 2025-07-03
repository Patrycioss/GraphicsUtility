#include <iostream>
#include <graphics_utility.hpp>
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

	while (!done) {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				done = true;
			}
		}

		SDL_GPUCommandBuffer* commandBuffer = SDL_AcquireGPUCommandBuffer(gpuDevice);
		if (commandBuffer == nullptr)
		{
			SDL_Log("AcquireGPUCommandBuffer failed: %s", SDL_GetError());
			return -1;
		}

		SDL_GPUTexture* swapchainTexture;
		if (!SDL_WaitAndAcquireGPUSwapchainTexture(commandBuffer, window, &swapchainTexture, nullptr, nullptr)) {
			SDL_Log("WaitAndAcquireGPUSwapchainTexture failed: %s", SDL_GetError());
			return -1;
		}

		if (swapchainTexture != nullptr)
		{
			SDL_GPUColorTargetInfo colorTargetInfo = { 0 };
			colorTargetInfo.texture = swapchainTexture;
			colorTargetInfo.clear_color = (SDL_FColor){ 0.3f, 0.4f, 0.5f, 1.0f };
			colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
			colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;

			SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(commandBuffer, &colorTargetInfo, 1, nullptr);
			SDL_EndGPURenderPass(renderPass);
		}

		SDL_SubmitGPUCommandBuffer(commandBuffer);
	}

	SDL_ReleaseWindowFromGPUDevice(gpuDevice, window);
	SDL_DestroyWindow(window);
	SDL_DestroyGPUDevice(gpuDevice);
	SDL_Quit();
	return 0;
}
