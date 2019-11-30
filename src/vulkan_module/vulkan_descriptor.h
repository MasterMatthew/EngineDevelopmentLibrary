#ifndef VULKAN_DESCRIPTOR_H
#define VULKAN_DESCRIPTOR_H

#include "vulkan/vulkan.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void createDescriptorPool(VkDescriptorPool* descriptorPool);
void destroyDescriptorPool(VkDescriptorPool descriptorPool);
void createDescriptorSetLayout(VkDescriptorSetLayout* descriptorSetLayout);
void destroyDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout);
void allocateDescriptorSet(const VkDescriptorPool descriptorPool, const VkDescriptorSetLayout descriptorSetLayout, VkDescriptorSet* descriptorSet);
void updateDescriptorSet(VkBuffer uniformBuffer, uint32_t range, VkImageView imageview, VkSampler sampler, VkDescriptorSet descriptorSet);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // !VULKAN_DESCRIPTOR_H