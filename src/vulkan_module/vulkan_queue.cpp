#include "vulkan_buffer.h"

void presentQueue(
	const uint32_t waitSemaphoreCount, const VkSemaphore* pwaitSemaphores,
	//const uint32_t swapchainCount, const VkSwapchainKHR* pSwapchains, 
	const uint32_t* pImageIndices) {
	VkPresentInfoKHR presentInfo = {};
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.pNext = NULL;
	presentInfo.waitSemaphoreCount = waitSemaphoreCount;
	presentInfo.pWaitSemaphores = pwaitSemaphores;
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &vulkan_swapchain;
	presentInfo.pImageIndices = pImageIndices;
	presentInfo.pResults = NULL;

	if (vkQueuePresentKHR(vulkan_graphics_queues[0], &presentInfo) != VK_SUCCESS) {
		printf("Failed to present!\n");
	}
}
