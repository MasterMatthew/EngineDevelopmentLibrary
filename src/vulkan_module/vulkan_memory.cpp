#include "vulkan_memory.h"

#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"

#include "vulkan_debug.h"
#include "vulkan_state.h"
#include "vulkan_memory_state.h"

void init_vulkan_memory() {
	VmaAllocatorCreateInfo info = {};
	info.physicalDevice = vulkan_physical_device;
	info.device = vulkan_logical_device;


	checkResult(vmaCreateAllocator(&info, &vulkan_memory_allocator), "Vulkan Memory Allocator Creation");
}


void term_vulkan_memory() {
	vmaDestroyAllocator(vulkan_memory_allocator);
}
