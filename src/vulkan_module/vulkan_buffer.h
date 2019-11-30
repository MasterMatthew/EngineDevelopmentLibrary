#ifndef VULKAN_BUFFER_H
#define VULKAN_BUFFER_H

#include "vulkan/vulkan.h"

#include "cglm/cglm.h"

#include "common_struct.h"

#include "vulkan_command_buffer.h"
#include "vulkan_constant.h"
#include "vulkan_create_info.h"
#include "vulkan_debug.h"
#include "vulkan_state.h"
#include "vulkan_struct.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//BUFFER
void createBuffer(const int size, const int usage, const VkMemoryPropertyFlags properties, VkBuffer* buffer, VkDeviceMemory *memory);
void destroyBuffer(VkBuffer buffer, VkDeviceMemory memory);
void createVertexBuffer(const VkCommandPool commandPool, VertexBufferCreateInfo *info, VertexBuffer *vertexBuffer);
void destroyVertexBuffer(VertexBuffer *vertexBuffer);
void copyBuffer(const VkCommandBuffer cb, const VkBuffer srcBuffer, const VkBuffer dstBuffer, const VkDeviceSize size);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // !VULKAN_BUFFER_H
