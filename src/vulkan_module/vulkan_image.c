#include "vulkan_image.h"

#include "vulkan_command_buffer.h"
#include "vulkan_constant.h"
#include "vulkan_state.h"


//IMAGEVIEW

void transitionImage(VkCommandBuffer cb, VkImage image, const VkFormat format, const VkImageLayout oldLayout, const VkImageLayout newLayout) {
	VkImageMemoryBarrier memoryBarrier;
	memoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	memoryBarrier.pNext = NULL;

	memoryBarrier.oldLayout = oldLayout;
	memoryBarrier.newLayout = newLayout;

	//Eventually this will matter
	memoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	memoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;

	memoryBarrier.image = image;
	memoryBarrier.subresourceRange = SUBRESOURCE_RANGE_COLOR;

	VkPipelineStageFlagBits srcMask, dstMask;
	//TODO: Fix this mess
	switch (oldLayout) {
	case VK_IMAGE_LAYOUT_UNDEFINED:
		memoryBarrier.srcAccessMask = 0;
		srcMask = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
		break;
	case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
		memoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		srcMask = VK_PIPELINE_STAGE_TRANSFER_BIT;
		break;
	}

	switch (newLayout) {
	case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
		memoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		dstMask = VK_PIPELINE_STAGE_TRANSFER_BIT;
		break;
	case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
		memoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
		//TODO: We could possible use the image in other pipeline stages
		dstMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		break;
	}

	vkCmdPipelineBarrier(cb, srcMask, dstMask, 0, 0, NULL, 0, NULL, 1, &memoryBarrier);
}

void copyBufferToImage(VkCommandBuffer cb, VkBuffer srcBuffer, VkImage dstImage, uint32_t imageWidth, uint32_t imageHeight) {
	VkBufferImageCopy copyRegion;
	copyRegion.bufferOffset = 0;
	copyRegion.bufferRowLength = 0;
	copyRegion.bufferImageHeight = 0;

	copyRegion.imageSubresource = SUBRESOURCE_LAYERS_COLOR;
	copyRegion.imageOffset = (VkOffset3D) { 0, 0, 0 };
	copyRegion.imageExtent = (VkExtent3D) { imageWidth, imageHeight, 1 };

	vkCmdCopyBufferToImage(cb, srcBuffer, dstImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copyRegion);
}

void createTextureImageView(const VkImage image, const VkFormat format, VkImageView *imageView) {
	VkImageViewCreateInfo viewInfo;
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.pNext = NULL;
	viewInfo.flags = 0;

	viewInfo.image = image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = format;

	viewInfo.subresourceRange = SUBRESOURCE_RANGE_COLOR;
	viewInfo.components = DEFAULT_COMPONENT_MAP;

	checkResult(vkCreateImageView(vulkan_logical_device, &viewInfo, NULL, imageView), "Texture ImageView creation");
}

void createTextureImage(const int width, const int height, const unsigned char* pixels, VkCommandPool commandPool, VkImage* image, VkDeviceMemory* imageMemory) {
	VkBuffer staging;
	VkDeviceMemory stagingMemory;

	int size = width * height * 4;

	createBuffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		&staging, &stagingMemory);

	void* data;
	vkMapMemory(vulkan_logical_device, stagingMemory, 0, size, 0, &data);
	memcpy(data, pixels, size);
	vkUnmapMemory(vulkan_logical_device, stagingMemory);


	VkImageCreateInfo imageInfo;
	imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageInfo.pNext = NULL;
	imageInfo.flags = 0;
	imageInfo.imageType = VK_IMAGE_TYPE_2D;
	imageInfo.extent.width = width;
	imageInfo.extent.height = height;
	imageInfo.extent.depth = 1;
	imageInfo.mipLevels = 1;
	imageInfo.arrayLayers = 1;
	imageInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
	imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
	imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
	imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageInfo.queueFamilyIndexCount = 0;
	imageInfo.pQueueFamilyIndices = NULL;

	checkResult(vkCreateImage(vulkan_logical_device, &imageInfo, NULL, image), "Image creation");


	VkMemoryRequirements req;
	vkGetImageMemoryRequirements(vulkan_logical_device, *image, &req);

	VkMemoryAllocateInfo allocInfo;
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.pNext = NULL;
	allocInfo.memoryTypeIndex = getMemoryType(req.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	allocInfo.allocationSize = req.size;

	checkResult(vkAllocateMemory(vulkan_logical_device, &allocInfo, NULL, imageMemory), "Image memory allocation");


	vkBindImageMemory(vulkan_logical_device, *image, *imageMemory, 0);

	VkCommandBuffer cb;
	allocateCommandBuffer(commandPool, &cb);
	vkBeginCommandBuffer(cb, &COMMAND_BUFFER_BEGIN_INFO);

	transitionImage(cb, *image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	copyBufferToImage(cb, staging, *image, width, height);
	transitionImage(cb, *image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	vkEndCommandBuffer(cb);
	submitQueue(0, NULL, NULL, 0, NULL, 1, &cb, NULL);
	vkQueueWaitIdle(vulkan_graphics_queues[0]);
	vkFreeCommandBuffers(vulkan_logical_device, commandPool, 1, &cb);
}