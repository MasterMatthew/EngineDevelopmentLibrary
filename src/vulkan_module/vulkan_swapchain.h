#ifndef VULKAN_SWAPCHAIN_H
#define VULKAN_SWAPCHAIN_H

#include "vulkan/vulkan.h"


void createSwapchain(const uint32_t window_width, const uint32_t window_height);
void destroySwapchain();
void recreateSwapchain(const uint32_t window_width, const uint32_t window_height);


// TEMPORARY FUNCTIONS

void presentQueue(
	const uint32_t waitSemaphoreCount, const VkSemaphore* pwaitSemaphores,
	//const uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, 
	const uint32_t* pImageIndices);

#endif // !VULKAN_SWAPCHAIN_H