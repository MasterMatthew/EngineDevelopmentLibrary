#ifndef VULKAN_COMMAND_BUFFER_H
#define VULKAN_COMMAND_BUFFER_H

#include "vulkan/vulkan.h"

#include "vulkan_debug.h"
#include "vulkan_struct.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// COMMAND BUFFER

void createGraphicsCommandPool(const VkCommandPoolCreateFlagBits flags, VkCommandPool *commandPool);
void createComputeCommandPool(const VkCommandPoolCreateFlagBits flags, VkCommandPool *commandPool);
void createTransferCommandPool(const VkCommandPoolCreateFlagBits flags, VkCommandPool *commandPool);
void allocateCommandBuffer(const VkCommandPool commandPool, VkCommandBuffer* commandBuffer);
void allocateCommandBuffers(const VkCommandPool commandPool, const uint32_t commandBufferCount, VkCommandBuffer* commandBuffers);

//void allocateSwapchainCommandBuffers(const VkCommandPool commandPool, uint32_t* commandBufferCount, VkCommandBuffer** commandBuffers);

// COMMAND BUFFER COMMANDS

void cmdBeginRenderpass(const VkCommandBuffer commandBuffer, const VkRenderPass renderpass, const VkFramebuffer framebuffer);
void cmdBindVertexBuffer(const VkCommandBuffer commandBuffer, const VertexBuffer vertexBuffer);


// CONSTANTS

//Doesn't cover secondary buffers
static const VkCommandBufferBeginInfo COMMAND_BUFFER_BEGIN_INFO =  {
	/*.sType = */ VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
	/*.pNext = */ NULL,
	/*.flags = */ 0,
	/*.pInheritanceInfo = */ NULL
};

static const VkCommandBufferBeginInfo COMMAND_BUFFER_BEGIN_INFO_ONE_TIME_SUBMIT = {
	/*.sType = */ VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
	/*.pNext = */ NULL,
	/*.flags = */ VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
	/*.pInheritanceInfo = */ NULL
};


// STATIC FUNCTIONS

//Submits the cb without any semaphores
/*
static void submitQueue(const VkQueue queue, const VkCommandBuffer *commandBuffer) {
	VkSubmitInfo sinfo;
	sinfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	sinfo.pNext = NULL;
	sinfo.commandBufferCount = 1;
	sinfo.pCommandBuffers = commandBuffer;
	sinfo.signalSemaphoreCount = 0;
	sinfo.pSignalSemaphores = NULL;
	sinfo.waitSemaphoreCount = 0;
	sinfo.pWaitSemaphores = NULL;
	sinfo.pWaitDstStageMask = NULL;

	vkQueueSubmit(queue, 1, &sinfo, NULL);
}
*/

// TEMPORARY FUNCTIONS

void submitQueue(
	const uint32_t waitSemaphoreCount, const VkSemaphore* pwaitSemaphores, const VkPipelineStageFlags* pWaitDstStageMask,
	const uint32_t signalSemaphoreCount, const VkSemaphore* pSignalSemaphores,
	const uint32_t commandBufferCount, const VkCommandBuffer* commandBuffer,
	const VkFence fence);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif // !VULKAN_COMMAND_BUFFER_H
