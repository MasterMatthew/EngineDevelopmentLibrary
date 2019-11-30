#include "vulkan_surface.h"

#include "vulkan_state.h"
#include "vulkan_debug.h"

//Creates a surface using win32 window handle
void createSurface(const uint32_t window_width, const uint32_t window_height, const void* hwnd, uint32_t* swapchainImageCount) {
	VkWin32SurfaceCreateInfoKHR info = {
		.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
		.pNext = NULL,
		.flags = 0,
		.hinstance = GetModuleHandle(NULL),
		.hwnd = hwnd
	};

	checkResult(vkCreateWin32SurfaceKHR(vulkan_instance, &info, NULL, &vulkan_surface), "Surface creation");

	VkBool32 present_support;
	checkResult(vkGetPhysicalDeviceSurfaceSupportKHR(vulkan_physical_device, vulkan_graphics_family, vulkan_surface, &present_support), "Surface support");
	printf("Surface support: %d\n", present_support);


	surface_width = window_width;
	surface_height = window_height;

	//Get Capabilities
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vulkan_physical_device, vulkan_surface, &vulkan_surface_capabilities);

	//Find Surface Format
	uint32_t surfaceFormatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(vulkan_physical_device, vulkan_surface, &surfaceFormatCount, NULL);
	VkSurfaceFormatKHR* surfaceFormats = malloc(surfaceFormatCount * sizeof(VkSurfaceFormatKHR));
	vkGetPhysicalDeviceSurfaceFormatsKHR(vulkan_physical_device, vulkan_surface, &surfaceFormatCount, surfaceFormats);

	vulkan_surface_format = surfaceFormats[0];
	for (int i = 1; i < surfaceFormatCount; i++) {
		if (surfaceFormats[i].format == VK_FORMAT_B8G8R8A8_UNORM && surfaceFormats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			vulkan_surface_format = surfaceFormats[i];
			break;
		}
	}

	//Find Present Mode
	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(vulkan_physical_device, vulkan_surface, &presentModeCount, NULL);
	VkPresentModeKHR* presentModes = malloc(presentModeCount * sizeof(VkPresentModeKHR));
	vkGetPhysicalDeviceSurfacePresentModesKHR(vulkan_physical_device, vulkan_surface, &presentModeCount, presentModes);

	vulkan_present_mode = VK_PRESENT_MODE_FIFO_KHR;
	for (int i = 0; i < presentModeCount; i++) {
		if (presentModes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR) {
			vulkan_present_mode = VK_PRESENT_MODE_IMMEDIATE_KHR;
			break;

		} if (presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR) {
			vulkan_present_mode = VK_PRESENT_MODE_MAILBOX_KHR;
		}
	}

	createSwapchain(window_width, window_height);

	*swapchainImageCount = vulkan_swapchain_image_count;
}

void destroySurface() {
	destroySwapchain();

	vkDestroySurfaceKHR(vulkan_instance, vulkan_surface, NULL);

	printf("Surface destroyed!\n");
}