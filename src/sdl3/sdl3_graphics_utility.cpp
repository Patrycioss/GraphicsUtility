#include <sdl3/sdl3_graphics_utility.hpp>
#include <utility>
#include <SDL3/SDL_log.h>

SDL3GraphicsUtility::SDL3GraphicsUtility(const SDL3Context context, SDL3TriangleSettings triangleSettings): GraphicsUtility(), context(context),
	triangleSettings(std::move(triangleSettings)) {
	init();
}

SDL3GraphicsUtility::SDL3GraphicsUtility(const SDL3Context context)
	: context(context), triangleSettings({"triangle.vert", "fragment.frag"}) {
	init();
}

SDL3GraphicsUtility::~SDL3GraphicsUtility() = default;

void SDL3GraphicsUtility::clear(const Colour& colour) {
	SDL_GPUColorTargetInfo colorTargetInfo = {nullptr};
	colorTargetInfo.texture = swapchainTexture;
	colorTargetInfo.clear_color = (SDL_FColor){0.3f, 0.4f, 0.5f, 1.0f};
	colorTargetInfo.load_op = SDL_GPU_LOADOP_CLEAR;
	colorTargetInfo.store_op = SDL_GPU_STOREOP_STORE;

	SDL_GPURenderPass* renderPass = SDL_BeginGPURenderPass(commandBuffer, &colorTargetInfo, 1, nullptr);
	SDL_EndGPURenderPass(renderPass);
}

void SDL3GraphicsUtility::startRendering() {
	commandBuffer = SDL_AcquireGPUCommandBuffer(context.gpuDevice);
	if (commandBuffer == nullptr) {
		SDL_Log("AcquireGPUCommandBuffer failed: %s", SDL_GetError());
		return;
	}

	if (!SDL_WaitAndAcquireGPUSwapchainTexture(commandBuffer, context.window, &swapchainTexture, nullptr, nullptr)) {
		SDL_Log("WaitAndAcquireGPUSwapchainTexture failed: %s", SDL_GetError());
		return;
	}
}

void SDL3GraphicsUtility::stopRendering() {
	SDL_SubmitGPUCommandBuffer(commandBuffer);
}

void SDL3GraphicsUtility::init() {
	SDL3Triangle::Init(context, triangleSettings);
}
