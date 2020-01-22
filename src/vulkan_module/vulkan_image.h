#ifndef VULKAN_IMAGE_H
#define VULKAN_IMAGE_H

#include "vulkan/vulkan.h"


static const VkImageSubresourceLayers SUBRESOURCE_LAYERS_COLOR = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };
static const VkImageSubresourceRange SUBRESOURCE_RANGE_COLOR = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
static const VkComponentMapping DEFAULT_COMPONENT_MAP = { VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY };

void createTextureImage(const int width, const int height, const unsigned char* pixels, VkCommandPool graphicsPool, VkImage* image, VkDeviceMemory* imageMemory);
void transitionImage(VkCommandBuffer cb, VkImage image, const VkFormat format, const VkImageLayout oldLayout, const VkImageLayout newLayout);
void copyBufferToImage(VkCommandBuffer cb, VkBuffer srcBuffer, VkImage dstImage, uint32_t imageWidth, uint32_t imageHeight);
void createTextureImageView(const VkImage image, const VkFormat format, VkImageView *imageView);

#endif // !VULKAN_IMAGE_H
