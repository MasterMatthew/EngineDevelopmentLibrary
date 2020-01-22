#include "vulkan_command_buffer.h"

#include "vulkan_state.h"


//COMMAND BUFFER

//Flags can be set to VK_COMMAND_POOL_CREATE_TRANSIENT_BIT and/or VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT
inline void createCommandPool(const uint32_t queueFamilyIndex, const VkCommandPoolCreateFlagBits flags, VkCommandPool *commandPool) {
	VkCommandPoolCreateInfo poolCreateInfo = {};
	poolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolCreateInfo.pNext = NULL;
	poolCreateInfo.flags = flags;
	poolCreateInfo.queueFamilyIndex = queueFamilyIndex;

	checkResult(vkCreateCommandPool(vulkan_logical_device, &poolCreateInfo, NULL, commandPool), "Command pool creation");
}
void createGraphicsCommandPool(const VkCommandPoolCreateFlagBits flags, VkCommandPool *commandPool) {
	createCommandPool(vulkan_graphics_family, flags, commandPool);
}
void createComputeCommandPool(const VkCommandPoolCreateFlagBits flags, VkCommandPool *commandPool) {
	createCommandPool(vulkan_compute_family, flags, commandPool);
}
void createTransferCommandPool(const VkCommandPoolCreateFlagBits flags, VkCommandPool *commandPool) {
	createCommandPool(vulkan_transfer_family, flags, commandPool);
}


void allocateCommandBuffer(const VkCommandPool commandPool, VkCommandBuffer* commandBuffer) {
	VkCommandBufferAllocateInfo allocateInfo;
	allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocateInfo.pNext = NULL;
	allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocateInfo.commandPool = commandPool;
	allocateInfo.commandBufferCount = 1;

	checkResult(vkAllocateCommandBuffers(vulkan_logical_device, &allocateInfo, commandBuffer), "Command buffer allocation");
}

void allocateCommandBuffers(const VkCommandPool commandPool, const uint32_t commandBufferCount, VkCommandBuffer* commandBuffers) {
	VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
	commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	commandBufferAllocateInfo.pNext = NULL;
	commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	commandBufferAllocateInfo.commandPool = commandPool;
	commandBufferAllocateInfo.commandBufferCount = commandBufferCount;

	checkResult(vkAllocateCommandBuffers(vulkan_logical_device, &commandBufferAllocateInfo, commandBuffers), "Command buffer allocation");
}

/*
void allocateSwapchainCommandBuffers(const VkCommandPool commandPool, uint32_t* commandBufferCount, VkCommandBuffer** commandBuffers) {
	VkCommandBufferAllocateInfo commandBufferAllocateInfo = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.pNext = NULL,
		.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		.commandPool = commandPool,
		.commandBufferCount = vulkan_swapchain_image_count
	};
	*commandBufferCount = vulkan_swapchain_image_count;
	*commandBuffers = malloc(vulkan_swapchain_image_count * sizeof(VkCommandBuffer));
	checkResult(vkAllocateCommandBuffers(vulkan_logical_device, &commandBufferAllocateInfo, *commandBuffers), "Command buffer allocation");
}
*/
// COMMAND BUFFER COMMANDS

void cmdBeginRenderpass(const VkCommandBuffer commandBuffer, const VkRenderPass renderpass, const VkFramebuffer framebuffer) {
	VkRenderPassBeginInfo renderpassInfo;
	renderpassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderpassInfo.pNext = NULL;
	renderpassInfo.renderPass = renderpass;
	renderpassInfo.renderArea.offset = { 0, 0 };
	renderpassInfo.renderArea.extent = vulkan_swapchain_extent;
	renderpassInfo.clearValueCount = 1;
	
	VkClearValue pClearValues = { 0.0f, 0.0f, 0.0f, 1.0f };
	renderpassInfo.pClearValues = &pClearValues; //TODO: POSSIBLE CAUSE OF CRASHES AS pClearValues goes out of scope
	renderpassInfo.framebuffer = framebuffer;

	vkCmdBeginRenderPass(commandBuffer, &renderpassInfo, VK_SUBPASS_CONTENTS_INLINE);
}

void cmdBindVertexBuffer(const VkCommandBuffer commandBuffer, const VertexBuffer vertexBuffer) {
	VkBuffer pBuffers[] = { vertexBuffer.buffer, vertexBuffer.buffer, vertexBuffer.buffer };

	vkCmdBindIndexBuffer(commandBuffer, vertexBuffer.buffer, 0, VK_INDEX_TYPE_UINT32);
	vkCmdBindVertexBuffers(commandBuffer, 0, 3, pBuffers, vertexBuffer.pOffsets);
}



void submitQueue(
	const uint32_t waitSemaphoreCount, const VkSemaphore* pwaitSemaphores, const VkPipelineStageFlags* pWaitDstStageMask,
	const uint32_t signalSemaphoreCount, const VkSemaphore* pSignalSemaphores,
	const uint32_t commandBufferCount, const VkCommandBuffer* commandBuffer,
	const VkFence fence) {

	VkSubmitInfo sinfo = {};
	sinfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	sinfo.pNext = NULL;
	sinfo.waitSemaphoreCount = waitSemaphoreCount;
	sinfo.pWaitSemaphores = pwaitSemaphores;
	sinfo.pWaitDstStageMask = pWaitDstStageMask;
	sinfo.signalSemaphoreCount = signalSemaphoreCount;
	sinfo.pSignalSemaphores = pSignalSemaphores;
	sinfo.commandBufferCount = commandBufferCount;
	sinfo.pCommandBuffers = commandBuffer;

	vkQueueSubmit(vulkan_graphics_queues[0], 1, &sinfo, fence);
}