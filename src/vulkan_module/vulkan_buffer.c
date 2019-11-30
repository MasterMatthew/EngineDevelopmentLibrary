#include "vulkan_buffer.h"

#include "vulkan_state.h"
#include "vulkan_image.h"
#include "vulkan_debug.h"

//FUNCTION

inline uint32_t getMemoryType(int filter, VkMemoryPropertyFlags properties) {
	//TODO: Branching
	for (uint32_t i = 0; i < vulkan_physical_device_memory_properties.memoryTypeCount; i++) {
		if (filter & (1 << i) && vulkan_physical_device_memory_properties.memoryTypes[i].propertyFlags & properties) return i;
	}

	fprintf(stderr, "Failed to find memory type!");
	return 0;
}


//BUFFER
void createBuffer(const int size, const int usage, const VkMemoryPropertyFlags properties, VkBuffer* buffer, VkDeviceMemory *memory) {
	VkBufferCreateInfo bufferInfo = {
		.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
		.pNext = NULL,
		.flags = 0,
		.size = size,
		.usage = usage,
		.sharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.queueFamilyIndexCount = 0,
		.pQueueFamilyIndices = NULL
	};

	checkResult(vkCreateBuffer(vulkan_logical_device, &bufferInfo, NULL, buffer), "Buffer creation");

	VkMemoryRequirements memoryRequirements;
	vkGetBufferMemoryRequirements(vulkan_logical_device, *buffer, &memoryRequirements);

	int memoryType = getMemoryType(memoryRequirements.memoryTypeBits, properties);

	VkMemoryAllocateInfo allocateInfo = { VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, NULL, memoryRequirements.size, memoryType };

	checkResult(vkAllocateMemory(vulkan_logical_device, &allocateInfo, NULL, memory), "Buffer memory allocation");
	checkResult(vkBindBufferMemory(vulkan_logical_device, *buffer, *memory, 0), "Memory binding");
}

void destroyBuffer(VkBuffer buffer, VkDeviceMemory memory) {
	vkDestroyBuffer(vulkan_logical_device, buffer, NULL);
	vkFreeMemory(vulkan_logical_device, memory, NULL);
}

void destroyVertexBuffer(VertexBuffer *vertexBuffer) {
	vkDestroyBuffer(vulkan_logical_device, vertexBuffer->buffer, NULL);
	vkFreeMemory(vulkan_logical_device, vertexBuffer->memory, NULL);
}

void copyBuffer(const VkCommandBuffer cb, const VkBuffer srcBuffer, const VkBuffer dstBuffer, const VkDeviceSize size) {
	vkCmdCopyBuffer(cb, srcBuffer, dstBuffer, 1, &(VkBufferCopy) { 0, 0, size });
}

//Processes a VertexBufferCreateInfo into a vertexBuffer
void createVertexBuffer(const VkCommandPool commandPool, const VertexBufferCreateInfo *info, VertexBuffer *vertexBuffer) {
	//Just in case the compiler doesn't do this for me
	uint32_t indicesCount = info->indicesCount;
	uint32_t* pIndices = info->pIndices;
	uint32_t attributeCount = info->attributeCount;
	uint32_t* pAttributeSizes = info->pAttributeSizes;
	uint32_t verticesCount = info->verticesCount;
	float* pVertices = info->pVertices;

	uint32_t indicesSize = indicesCount * sizeof(uint32_t);

	//Set half of the variables in vertexBuffer, buffer and memory will be set later
	vertexBuffer->indicesCount = indicesCount;
	vertexBuffer->attributeCount = attributeCount;
	VkDeviceSize* pOffsets = vertexBuffer->pOffsets = malloc(attributeCount * sizeof(uint32_t));

	uint32_t verticesSize = 0;
	//Calculate the totale size of all vertices as well as the offsets of each attribute
	for (int i = 0; i < attributeCount; i++) {
		pOffsets[i] = indicesSize + verticesSize;
		verticesSize += pAttributeSizes[i] * verticesCount;
	}
	uint32_t size = indicesSize + verticesSize;

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingMemory;

	createBuffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, &stagingBuffer, &stagingMemory);

	void* data;
	checkResult(vkMapMemory(vulkan_logical_device, stagingMemory, 0, size, 0, &data), "Memory mapping");
	memcpy(data, pIndices, indicesSize);
	memcpy((char*)data + indicesSize, pVertices, verticesSize);
	vkUnmapMemory(vulkan_logical_device, stagingMemory);

	createBuffer(size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, &vertexBuffer->buffer, &vertexBuffer->memory);

	VkCommandBuffer cb;
	allocateCommandBuffer(commandPool, &cb);
	vkBeginCommandBuffer(cb, &COMMAND_BUFFER_BEGIN_INFO);

	copyBuffer(cb, stagingBuffer, vertexBuffer->buffer, size);

	vkEndCommandBuffer(cb);
	submitQueue(0, NULL, NULL, 0, NULL, 1, &cb, NULL);
	vkQueueWaitIdle(vulkan_graphics_queues[0]);
	vkFreeCommandBuffers(vulkan_logical_device, commandPool, 1, &cb);
	destroyBuffer(stagingBuffer, stagingMemory);
}