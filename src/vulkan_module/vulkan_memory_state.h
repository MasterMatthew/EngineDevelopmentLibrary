#ifndef VULKAN_MEMORY_STATE_H
#define VULKAN_MEMORY_STATE_H

#include <unordered_map>

//#define VMA_IMPLEMENTATION
#include "vk_mem_alloc.h"


extern VmaAllocator vulkan_memory_allocator;
extern std::unordered_map<VkBuffer, VmaAllocation> vulkan_memory_allocations;


#endif // !VULKAN_MEMORY_STATE_H
