#pragma once
#include <graphics_utility.hpp>
#include <SDL3/SDL_gpu.h>

class SDL3GraphicsUtility final : public GraphicsUtility
{
public: // Properties
    
private: // Member Variables
    SDL_GPUDevice* gpuDevice;
    SDL_Window* window;

    SDL_GPUCommandBuffer* commandBuffer{};
    SDL_GPUTexture* swapchainTexture{};
    
public: // Public Functions
    SDL3GraphicsUtility(SDL_GPUDevice* gpuDevice, SDL_Window* window);
    ~SDL3GraphicsUtility() override;
    
    SDL3GraphicsUtility(const SDL3GraphicsUtility&) = delete;
    SDL3GraphicsUtility(SDL3GraphicsUtility&&) = delete;
    SDL3GraphicsUtility& operator=(const SDL3GraphicsUtility&) = delete;

    void clear(const Colour& colour) override;

    void startRendering() override;
    void stopRendering() override;
    
private: // Private Methods
};
