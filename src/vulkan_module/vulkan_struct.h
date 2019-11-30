#ifndef VULKAN_STRUCT_H
#define VULKAN_STRUCT_H

#include "cglm/cglm.h"
#include "vulkan/vulkan.h"

//structures related to vertices and buffers

typedef struct vertex {
	vec3 pos;
	vec3 normal;
	vec2 texCoord;
} vertex;

typedef struct buffer_object {
	mat4 model;
	mat4 view;
	mat4 proj;
} buffer_object;

typedef struct VertexBuffer {
	VkBuffer buffer;
	VkDeviceMemory memory;
	uint32_t indicesCount;
	uint32_t attributeCount;
	VkDeviceSize* pOffsets;
} VertexBuffer;

#endif // !VULKAN_STRUCT_H