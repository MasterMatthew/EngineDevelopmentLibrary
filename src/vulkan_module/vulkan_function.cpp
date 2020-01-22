#include "vulkan_function.h"

#include "vulkan_state.h"

//FUNCTION

uint32_t getMemoryType(int filter, VkMemoryPropertyFlags properties) {
	//TODO: Branching
	for (uint32_t i = 0; i < vulkan_physical_device_memory_properties.memoryTypeCount; i++) {
		if (filter & (1 << i) && vulkan_physical_device_memory_properties.memoryTypes[i].propertyFlags & properties) return i;
	}

	//fprintf(stderr, "Failed to find memory type!");
	return 0;
}