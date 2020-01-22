#include "vulkan_memory_state.h"

VmaAllocator vulkan_memory_allocator = 0;

std::unordered_map<VkBuffer, VmaAllocation> vulkan_memory_allocations = {};