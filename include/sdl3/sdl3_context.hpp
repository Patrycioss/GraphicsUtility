#pragma once

#include <string>
#include <SDL3/SDL.h>

struct SDL3Context {
	SDL_GPUDevice* gpuDevice;
	SDL_Window* window;
	std::string resourcesPath = "resources";
	std::string compiledShaderPath = "shaders/compiled";
};