/*
This file contains all functionality related to vulkan queues
*/
#ifndef VULKAN_QUEUE_H
#define VULKAN_QUEUE_H

#include "vulkan/vulkan.h"


void presentQueue(
	const uint32_t waitSemaphoreCount, const VkSemaphore* pwaitSemaphores,
	//const uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, 
	const uint32_t* pImageIndices);

#endif // !VULKAN_QUEUE_H
