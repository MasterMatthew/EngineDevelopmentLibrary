/*
This file contains all functionality related to vulkan buffers
*/
#ifndef VULKAN_BUFFER_H
#define VULKAN_BUFFER_H

#include "vulkan/vulkan.h"

//#include "cglm/cglm.h"

#include "common_struct.h"

#include "vulkan_command_buffer.h"
#include "vulkan_constant.h"
#include "vulkan_debug.h"
#include "vulkan_state.h"
#include "vulkan_struct.h"


// BUFFER

/**
Creates a vulkan memory buffer

@param size The size in bytes of the buffer
@param usage A bitmask of VkBufferUsageFlagBits that specifies the allowed usages of the buffer
@param properties Memory properties requires by the buffer
@param buffer Pointer to the created buffer
@param memory Pointer to the device memory allocated for the buffer
*/
void createBuffer(const int size, const int usage, const VkMemoryPropertyFlags properties, VkBuffer* buffer, VkDeviceMemory* memory);
/**
Destroy a vulkan memory buffer and release it's allocated memory

@param buffer The buffer to be destroyed
@param memory The associated allocation of memory to be released
*/
void destroyBuffer(VkBuffer buffer, VkDeviceMemory memory);

void createVertexBuffer(VkCommandPool commandPool, VertexBufferCreateInfo *info, VertexBuffer *vertexBuffer);
void destroyVertexBuffer(VertexBuffer *vertexBuffer);

void copyBuffer(const VkCommandBuffer cb, const VkBuffer srcBuffer, const VkBuffer dstBuffer, const VkDeviceSize size);

#endif // !VULKAN_BUFFER_H
