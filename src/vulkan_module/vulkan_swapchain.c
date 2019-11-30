#include "vulkan_swapchain.h"

#include "vulkan_state.h"
#include "vulkan_image.h"
#include "vulkan_debug.h"

void createSwapchain(const uint32_t window_width, const uint32_t window_height) {
	//Determine swapchain extent
	if (vulkan_surface_capabilities.currentExtent.width == UINT32_MAX) {
		vulkan_swapchain_extent = (VkExtent2D) {
			max(vulkan_surface_capabilities.minImageExtent.width, min(vulkan_surface_capabilities.maxImageExtent.width, window_width)),
				max(vulkan_surface_capabilities.minImageExtent.height, min(vulkan_surface_capabilities.maxImageExtent.height, window_height))
		};
	}
	else {
		vulkan_swapchain_extent = vulkan_surface_capabilities.currentExtent;
	}

	//Create the presentation swapchain
	uint32_t imageCount = vulkan_surface_capabilities.minImageCount;
	if (vulkan_surface_capabilities.maxImageCount > 0 && imageCount > vulkan_surface_capabilities.maxImageCount) 
		imageCount = vulkan_surface_capabilities.maxImageCount;

	VkSwapchainCreateInfoKHR swapchainCreateInfo;
	swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchainCreateInfo.flags = 0;
	swapchainCreateInfo.pNext = NULL;

	swapchainCreateInfo.surface = vulkan_surface;
	swapchainCreateInfo.minImageCount = imageCount;
	swapchainCreateInfo.imageFormat = vulkan_surface_format.format;
	swapchainCreateInfo.imageColorSpace = vulkan_surface_format.colorSpace;
	swapchainCreateInfo.imageExtent = vulkan_swapchain_extent;
	swapchainCreateInfo.imageArrayLayers = 1;
	swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapchainCreateInfo.queueFamilyIndexCount = 0;
	swapchainCreateInfo.pQueueFamilyIndices = NULL;

	swapchainCreateInfo.preTransform = vulkan_surface_capabilities.currentTransform;
	swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchainCreateInfo.presentMode = vulkan_present_mode;
	swapchainCreateInfo.clipped = VK_TRUE;
	swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

	checkResult(vkCreateSwapchainKHR(vulkan_logical_device, &swapchainCreateInfo, NULL, &vulkan_swapchain), "Swapchain creation");

	vkGetSwapchainImagesKHR(vulkan_logical_device, vulkan_swapchain, &vulkan_swapchain_image_count, NULL);
	vulkan_swapchain_images = malloc(vulkan_swapchain_image_count * sizeof(VkImage));
	vkGetSwapchainImagesKHR(vulkan_logical_device, vulkan_swapchain, &vulkan_swapchain_image_count, vulkan_swapchain_images);
	printf("Swapchain images retrieved!\n");

	vulkan_swapchain_imageviews = malloc(vulkan_swapchain_image_count * sizeof(VkImageView));

	VkImageViewCreateInfo imageViewCreateInfo;
	imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	imageViewCreateInfo.flags = 0;
	imageViewCreateInfo.pNext = NULL;
	imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	imageViewCreateInfo.format = vulkan_surface_format.format;
	imageViewCreateInfo.components = DEFAULT_COMPONENT_MAP;
	imageViewCreateInfo.subresourceRange = SUBRESOURCE_RANGE_COLOR;

	for (int i = 0; i < vulkan_swapchain_image_count; i++) {
		imageViewCreateInfo.image = vulkan_swapchain_images[i];

		checkResult(vkCreateImageView(vulkan_logical_device, &imageViewCreateInfo, NULL, &(vulkan_swapchain_imageviews[i])), "Swapchain imageview creation");
	}
}

void destroySwapchain() {

	vkDestroySwapchainKHR(vulkan_logical_device, vulkan_swapchain, NULL);

	for (int i = 0; i < vulkan_swapchain_image_count; i++) {
		vkDestroyImageView(vulkan_logical_device, vulkan_swapchain_imageviews[i], NULL);
	}

	printf("Swapchain destroyed!\n");
}

void recreateSwapchain(const uint32_t window_width, const uint32_t window_height) {
	destroySwapchain();
	createSwapchain(window_width, window_height);
}


// TEMPORARY FUNCTIONS

void presentQueue(
	const uint32_t waitSemaphoreCount, const VkSemaphore* pwaitSemaphores,
	//const uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, 
	const uint32_t* pImageIndices) {
	VkPresentInfoKHR presentInfo = {
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.pNext = NULL,
		.waitSemaphoreCount = waitSemaphoreCount,
		.pWaitSemaphores = pwaitSemaphores,
		.swapchainCount = 1,
		.pSwapchains = &vulkan_swapchain,
		.pImageIndices = pImageIndices,
		.pResults = NULL
	};

	if (vkQueuePresentKHR(vulkan_graphics_queues[0], &presentInfo) != VK_SUCCESS) {
		printf("Failed to present!\n");
	}
}
