#ifndef VULKAN_INIT_H
#define VULKAN_INIT_H

#include <stdlib.h>

#include "vulkan/vulkan.h"
#include "cglm/cglm.h"

#include "common_struct.h"

#include "vulkan_struct.h"
#include "vulkan_create_info.h"

//TODO: Split physical device picking

/**
Initializes primary vulkan systems

Operations:
Creates a vulkan instance
Gets all vulkan physical devices and determines an appropriate physical device
Creates a vulkan logical device (vulkan device)
Gets all vulkan queue families (all families available on physical device)
Gets all vulkan queues (gets every queue available on physical device)

@param applicationName The name of the application
@param engineName The name of the engine
@param requestedLayers *UNIMPLEMENTED* The required vulkan layers
@param requesedExtension *UNIMPLEMENTED* The required vulkan extensions
*/
void initVulkan(const char *applicationName, const char *engineName, const string_array &requestedLayers, const string_array &requestedExtension);

/**
Destroys all state created by initVulkan

NOTE: All vulkan state created outside of initVulkan should be disposed of properly before calling this function
*/
void termVulkan();


//TODO: Move somewhere else

//SAMPLER

void createSampler(VkSampler *sampler);


//TEMPORARY FUNCTIONS

void createSwapchainFramebuffer(const VkRenderPass renderpass, const uint32_t imageIndex, VkFramebuffer *framebuffer);
void updateDescriptorBuffers(VkBuffer uniformBuffer, VkImageView texture, VkSampler sampler, VkDescriptorSet descriptorSet);

void updateUniformBuffer(VkDeviceMemory uniformBufferMemory);

void createSemaphore(VkSemaphore *semaphore);
void createFence(VkFence *fence);
void createSignaledFence(VkFence *fence);

void getNextImageIndex(const VkSemaphore semaphore, uint32_t *index);

#endif // !VULKAN_INIT_H
