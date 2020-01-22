#ifndef VULKAN_INIT_H
#define VULKAN_INIT_H

#include <stdlib.h>

#include "vulkan/vulkan.h"
#include "cglm/cglm.h"

#include "common_struct.h"

#include "vulkan_struct.h"
#include "vulkan_create_info.h"

void initVulkan(const char *applicationName, const char *engineName, const string_array &requestedLayers, const string_array &requestedExtension);
void termVulkan();

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
