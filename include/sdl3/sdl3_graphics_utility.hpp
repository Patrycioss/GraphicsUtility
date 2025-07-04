#pragma once
#include <graphics_utility.hpp>
#include <SDL3/SDL_gpu.h>

#include "sdl3_context.hpp"
#include "triangle/sdl3_triangle_settings.hpp"
#include "triangle/sdl3_triangle.hpp"


class SDL3GraphicsUtility final : public GraphicsUtility {
public: // Properties

private: // Member Variables
	SDL3Context context;
	SDL3TriangleSettings triangleSettings;

	SDL_GPUCommandBuffer* commandBuffer{};
	SDL_GPUTexture* swapchainTexture{};

public: // Public Functions
	SDL3GraphicsUtility(SDL3Context context, SDL3TriangleSettings triangleSettings);
	explicit SDL3GraphicsUtility(SDL3Context context);
	~SDL3GraphicsUtility() override;

	SDL3GraphicsUtility(const SDL3GraphicsUtility&) = delete;
	SDL3GraphicsUtility(SDL3GraphicsUtility&&) = delete;
	SDL3GraphicsUtility& operator=(const SDL3GraphicsUtility&) = delete;

	void clear(const Colour& colour) override;

	void startRendering() override;
	void stopRendering() override;

private: // Private Methods
	void init();
};
