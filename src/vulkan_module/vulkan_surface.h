/*
This file contains surface relevant functions
*/

#ifndef VULKAN_SURFACE_H
#define VULKAN_SURFACE_H

#include "vulkan/vulkan.h"

/**
Creates a vulkan surface attached to a window

NOTE: The surface state is stored in vulkan_state and is hidden, if direct access is required then define VULKAN_MODULE_EXPOSE_STATE before including vulkan_module.h

@param width The width of the surface
@param height The height of the surface
@param window_handle The handle to a window (eg. an HWND on windows)
@param[out] swapchainImageCount Returns the number of images the swapchain will need
*/
void createSurface(const uint32_t width, const uint32_t height, const void* window_handle, uint32_t* swapchainImageCount);

/**
Destroys the vulkan surface stored in vulkan_state
*/
void destroySurface();

#endif // !VULKAN_SURFACE_H