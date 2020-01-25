#include "vulkan_memory.h"

//#define VMA_IMPLEMENTATION
//#include "vk_mem_alloc.h"

#include "vulkan_debug.h"
#include "vulkan_state.h"

// FUNCTIONS

uint32_t getMemoryType(int filter, VkMemoryPropertyFlags properties) {
	//TODO: Branching
	for (uint32_t i = 0; i < vulkan_physical_device_memory_properties.memoryTypeCount; i++) {
		if (filter & (1 << i) && vulkan_physical_device_memory_properties.memoryTypes[i].propertyFlags & properties) return i;
	}

	fprintf(stderr, "Failed to find memory type!");
	return 0;
}

/*
void init_vulkan_memory() {
	VmaAllocatorCreateInfo info = {};
	info.physicalDevice = vulkan_physical_device;
	info.device = vulkan_logical_device;


	checkResult(vmaCreateAllocator(&info, &vulkan_memory_allocator), "Vulkan Memory Allocator Creation");
}


void term_vulkan_memory() {
	vmaDestroyAllocator(vulkan_memory_allocator);
}
*/