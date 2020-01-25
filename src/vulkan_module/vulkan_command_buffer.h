/*
This file contains all functionality related to command buffers
*/
#ifndef VULKAN_COMMAND_BUFFER_H
#define VULKAN_COMMAND_BUFFER_H

#include "vulkan/vulkan.h"

#include "vulkan_debug.h"
#include "vulkan_struct.h"

// COMMAND BUFFER

/**
Creates a command pool using the graphics queue family

@param flags Command pool creation flag bits, refer to vulkan documentation
@param commandPool Pointer to the created commandPool
*/
void createGraphicsCommandPool(const VkCommandPoolCreateFlagBits flags, VkCommandPool *commandPool);
/**
Creates a command pool using the compute queue family

@param flags Command pool creation flag bits, refer to vulkan documentation
@param commandPool Pointer to the created commandPool
*/
void createComputeCommandPool(const VkCommandPoolCreateFlagBits flags, VkCommandPool *commandPool);
/**
Creates a command pool using the transfer queue family

@param flags Command pool creation flag bits, refer to vulkan documentation
@param commandPool Pointer to the created commandPool
*/
void createTransferCommandPool(const VkCommandPoolCreateFlagBits flags, VkCommandPool *commandPool);

/**
Allocates a single command buffer from a given command pool

@param commandPool The command pool used to allocate the command buffer
@param commandBuffer Pointer to the allocated command buffer
*/
void allocateCommandBuffer(const VkCommandPool commandPool, VkCommandBuffer* commandBuffer);
/**
Allocates a number of command buffers from a given command pool

@param commandPool The command pool used to allocate the command buffers
@param commandBufferCount The number of command buffers to allocate
@param commandBuffer Pointer to the allocated command buffers
*/
void allocateCommandBuffers(const VkCommandPool commandPool, const uint32_t commandBufferCount, VkCommandBuffer* commandBuffers);

//void allocateSwapchainCommandBuffers(const VkCommandPool commandPool, uint32_t* commandBufferCount, VkCommandBuffer** commandBuffers);

// COMMAND BUFFER COMMANDS

/**
Calls vkCmdBeginRenderpass with the given parameters

@param commandBuffer The command buffer to function on
@param renderpass The renderpass to attach to the command buffer
@param framebuffer The framebuffer to attach to the renderpass
*/
void cmdBeginRenderpass(const VkCommandBuffer commandBuffer, const VkRenderPass renderpass, const VkFramebuffer framebuffer);
/**
Binds a vertex buffer to the command buffer

@param commandBuffer The command buffer to function on
@param vertexBuffer The vertex buffer to bind to the command buffer
*/
void cmdBindVertexBuffer(const VkCommandBuffer commandBuffer, const VertexBuffer vertexBuffer);


// CONSTANTS

/**
Basic command buffer begin info
NOTE: Doesn't cover secondary buffers
*/
static const VkCommandBufferBeginInfo COMMAND_BUFFER_BEGIN_INFO =  {
	/*.sType = */ VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
	/*.pNext = */ NULL,
	/*.flags = */ 0,
	/*.pInheritanceInfo = */ NULL
};

/**
Basic command buffer begin info for a single submition
NOTE: Doesn't cover secondary buffers
*/
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

#endif // !VULKAN_COMMAND_BUFFER_H
