#ifndef VULKAN_SWAPCHAIN_H
#define VULKAN_SWAPCHAIN_H

#include "vulkan/vulkan.h"

/**
Creates a new swapchain

NOTE: State information about the swapchain is stored in vulkan_state

@param width The width of the swapchain images
@param height The height of the swapchain images
*/
void createSwapchain(const uint32_t width, const uint32_t height);

/**
Destroy the current swapchain
*/
void destroySwapchain();

/**
Recreates the swapchain
Destroys the previous swapchain and creates a new one

@param width The width of the swapchain images
@param height The height of the swapchain images
*/
void recreateSwapchain(const uint32_t width, const uint32_t height);


// TEMPORARY FUNCTIONS

void presentQueue(
	const uint32_t waitSemaphoreCount, const VkSemaphore* pwaitSemaphores,
	//const uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, 
	const uint32_t* pImageIndices);

#endif // !VULKAN_SWAPCHAIN_H