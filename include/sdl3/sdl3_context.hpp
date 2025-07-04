#pragma once

#include <SDL3/SDL.h>

struct SDL3Context {
	SDL_GPUDevice* gpuDevice;
	SDL_Window* window;
};