#ifndef VULKAN_DEBUG_H
#define VULKAN_DEBUG_H

#include <stdio.h>

#include "vulkan/vulkan.h"

#ifdef __cplusplus
extern "C" {
#ifdef UNDEFINED //Exists solely so that I can enter without getting auto-tabbed in
}
#endif
#endif // __cplusplus


//Prints the result of a vulkan API call
static void checkResult(VkResult result, char* action) {
	#ifdef _DEBUG

	if (result == VK_SUCCESS) { printf("%s: SUCCESS!\n", action); return; }

	fprintf(stderr, "%s: FAILED - ", action);

	switch (result) {
	case VK_ERROR_OUT_OF_HOST_MEMORY:
		fprintf(stderr, "Out of host Memory!\n");
		break;
	case VK_ERROR_OUT_OF_DEVICE_MEMORY:
		fprintf(stderr, "Out of device Memory!\n");
		break;
	case VK_ERROR_INITIALIZATION_FAILED:
		fprintf(stderr, "Initialization failed!\n");
		break;
	case VK_ERROR_LAYER_NOT_PRESENT:
		fprintf(stderr, "Layer not present!\n");
		break;
	case VK_ERROR_EXTENSION_NOT_PRESENT:
		fprintf(stderr, "Extension not present!\n");
		break;
	case VK_ERROR_FEATURE_NOT_PRESENT:
		fprintf(stderr, "Feature not present!\n");
		break;
	case VK_ERROR_TOO_MANY_OBJECTS:
		fprintf(stderr, "Too many objects!\n");
		break;
	case VK_ERROR_INCOMPATIBLE_DRIVER:
		fprintf(stderr, "Incompatible driver!\n");
		break;
	case VK_ERROR_DEVICE_LOST:
		fprintf(stderr, "Device lost!\n");
		break;
	case VK_ERROR_INVALID_SHADER_NV:
		fprintf(stderr, "Invalid shader!\n");
		break;
	default:
		fprintf(stderr, "Unknown error!\n");
		break;
	}
	#endif // _DEBUG
}

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // !VULKAN_DEBUG_H