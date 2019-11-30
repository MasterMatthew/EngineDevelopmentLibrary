#ifndef VULKAN_CONSTANT_H
#define VULKAN_CONSTANT_H

#include "vulkan/vulkan.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// SEMAPHORES //

//Semaphores currently only have one possible create info
static const VkSemaphoreCreateInfo SEMAPHORE_CREATE_INFO = {
	/*.sType = */ VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
	/*.pNext = */ NULL,
	/*.flags =*/  0
};

// FENCES //

//Fences have two basic create infos
//It is possible to do something extra with the pNext field though
static const VkFenceCreateInfo FENCE_CREATE_INFO = {
	/*.sType = */ VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
	/*.pNext = */ NULL,
	/*.flags = */ VK_FENCE_CREATE_SIGNALED_BIT
};

static const VkFenceCreateInfo FENCE_CREATE_INFO_SIGNALED = {
	/*.sType = */ VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
	/*.pNext = */ NULL,
	/*.flags = */ VK_FENCE_CREATE_SIGNALED_BIT
};


#ifdef __cplusplus
}
#endif // __cplusplus
#endif // VULKAN_CONSTANT_H