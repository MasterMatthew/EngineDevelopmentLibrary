/*
This file contains functionality to debug vulkan systems
*/
#ifndef VULKAN_DEBUG_H
#define VULKAN_DEBUG_H

//#include <stdio.h>

#include "logger.h"
#include "vulkan/vulkan.h"

static void* vulkan_logger_instance() {
	return default_logger_instance();
	//return console_logger("VULKAN");
}

//Prints the result of a vulkan API call
static void checkResult(VkResult result, char* action) {
	#ifdef _DEBUG
	
	if (result == VK_SUCCESS) { 
		LOG_LOGGER_DEBUG(vulkan_logger_instance(), "%s: SUCCESS!", action);
		return; 
	}

	switch (result) {
	case VK_ERROR_OUT_OF_HOST_MEMORY:
		LOG_LOGGER_ERROR(vulkan_logger_instance(), "%s: FAILED - %s", action, "Out of host Memory!");
		break;
	case VK_ERROR_OUT_OF_DEVICE_MEMORY:
		LOG_LOGGER_ERROR(vulkan_logger_instance(), "%s: FAILED - %s", action, "Out of device Memory!");
		break;
	case VK_ERROR_INITIALIZATION_FAILED:
		LOG_LOGGER_ERROR(vulkan_logger_instance(), "%s: FAILED - %s", action, "Initialization failed!");
		break;
	case VK_ERROR_LAYER_NOT_PRESENT:
		LOG_LOGGER_ERROR(vulkan_logger_instance(), "%s: FAILED - %s", action, "Layer not present!");
		break;
	case VK_ERROR_EXTENSION_NOT_PRESENT:
		LOG_LOGGER_ERROR(vulkan_logger_instance(), "%s: FAILED - %s", action, "Extension not present!");
		break;
	case VK_ERROR_FEATURE_NOT_PRESENT:
		LOG_LOGGER_ERROR(vulkan_logger_instance(), "%s: FAILED - %s", action, "Feature not present!");
		break;
	case VK_ERROR_TOO_MANY_OBJECTS:
		LOG_LOGGER_ERROR(vulkan_logger_instance(), "%s: FAILED - %s", action, "Too many objects!");
		break;
	case VK_ERROR_INCOMPATIBLE_DRIVER:
		LOG_LOGGER_ERROR(vulkan_logger_instance(), "%s: FAILED - %s", action, "Incompatible driver!");
		break;
	case VK_ERROR_DEVICE_LOST:
		LOG_LOGGER_ERROR(vulkan_logger_instance(), "%s: FAILED - %s", action, "Device lost!");
		break;
	case VK_ERROR_INVALID_SHADER_NV:
		LOG_LOGGER_ERROR(vulkan_logger_instance(), "%s: FAILED - %s", action, "Invalid shader!");
		break;
	default:
		LOG_LOGGER_ERROR(vulkan_logger_instance(), "%s: FAILED - %s", action, "Unknown error!");
		break;
	}
	#endif // _DEBUG
}

#endif // !VULKAN_DEBUG_H