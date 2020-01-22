#ifndef VULKAN_SURFACE_H
#define VULKAN_SURFACE_H

#include "vulkan/vulkan.h"


void createSurface(const uint32_t window_width, const uint32_t window_height, const void* hwnd, uint32_t* swapchainImageCount);
void destroySurface();

#endif // !VULKAN_SURFACE_H