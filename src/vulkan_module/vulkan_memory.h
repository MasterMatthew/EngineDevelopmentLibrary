/*
This file contains all functionality related to vulkan memory
*/
#ifndef VULKAN_MEMORY_H
#define VULKAN_MEMORY_H

#include "vulkan/vulkan.h"

// FUNCTIONS

/**

@param filter 
*/
uint32_t getMemoryType(int filter, VkMemoryPropertyFlags properties);

//void init_vulkan_memory();
//void term_vulkan_memory();


#endif // !VULKAN_MEMORY_H
