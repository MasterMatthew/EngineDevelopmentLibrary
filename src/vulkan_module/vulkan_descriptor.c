#include "vulkan_descriptor.h"

#include "vulkan_state.h"
#include "vulkan_image.h"
#include "vulkan_debug.h"


//DESCRIPTOR SETS

void createDescriptorPool(VkDescriptorPool* descriptorPool) {
	VkDescriptorPoolSize *poolSize = (VkDescriptorPoolSize[]) {
		{
			.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				.descriptorCount = 1
		}, {
			.type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			.descriptorCount = 1
		}
	};

	VkDescriptorPoolCreateInfo poolCreateInfo;
	poolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolCreateInfo.pNext = NULL;
	poolCreateInfo.flags = 0;
	poolCreateInfo.poolSizeCount = 2;
	poolCreateInfo.pPoolSizes = poolSize;
	poolCreateInfo.maxSets = 1;

	checkResult(vkCreateDescriptorPool(vulkan_logical_device, &poolCreateInfo, NULL, descriptorPool), "Descriptor pool creation");
}

void destroyDescriptorPool(VkDescriptorPool descriptorPool) {
	vkDestroyDescriptorPool(vulkan_logical_device, descriptorPool, NULL);
}

void createDescriptorSetLayout(VkDescriptorSetLayout* descriptorSetLayout) {
	VkDescriptorSetLayoutBinding* bindings = (VkDescriptorSetLayoutBinding[]) {
		{
			.binding = 0,
				.descriptorCount = 1,
				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				.stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
				.pImmutableSamplers = NULL
		}, {
			.binding = 1,
			.descriptorCount = 1,
			.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
			.pImmutableSamplers = NULL
		}
	};

	VkDescriptorSetLayoutCreateInfo layoutInfo;
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.pNext = NULL;
	layoutInfo.flags = 0;
	layoutInfo.bindingCount = 2;
	layoutInfo.pBindings = bindings;

	checkResult(vkCreateDescriptorSetLayout(vulkan_logical_device, &layoutInfo, NULL, descriptorSetLayout), "Descriptor set layout creation");
}

void destroyDescriptorSetLayout(VkDescriptorSetLayout descriptorSetLayout) {
	vkDestroyDescriptorSetLayout(vulkan_logical_device, descriptorSetLayout, NULL);
}

void allocateDescriptorSet(const VkDescriptorPool descriptorPool, const VkDescriptorSetLayout descriptorSetLayout, VkDescriptorSet* descriptorSet) {
	VkDescriptorSetAllocateInfo setAllocateInfo;
	setAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	setAllocateInfo.pNext = NULL;
	setAllocateInfo.descriptorPool = descriptorPool;
	setAllocateInfo.descriptorSetCount = 1;
	setAllocateInfo.pSetLayouts = &descriptorSetLayout;

	checkResult(vkAllocateDescriptorSets(vulkan_logical_device, &setAllocateInfo, descriptorSet), "Descriptor set allocation");
}

void updateDescriptorSet(VkBuffer uniformBuffer, uint32_t range, VkImageView imageview, VkSampler sampler, VkDescriptorSet descriptorSet) {
	VkDescriptorBufferInfo bufferInfo;
	bufferInfo.buffer = uniformBuffer;
	bufferInfo.offset = 0;
	bufferInfo.range = range;

	VkDescriptorImageInfo imageInfo;
	imageInfo.imageView = imageview;
	imageInfo.sampler = sampler;
	imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

	VkWriteDescriptorSet *writeDescriptorSet = malloc(sizeof(VkWriteDescriptorSet) * 2);
	writeDescriptorSet[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	writeDescriptorSet[0].pNext = NULL;
	writeDescriptorSet[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	writeDescriptorSet[0].descriptorCount = 1;
	writeDescriptorSet[0].dstSet = descriptorSet;
	writeDescriptorSet[0].dstBinding = 0;
	writeDescriptorSet[0].dstArrayElement = 0;
	writeDescriptorSet[0].pBufferInfo = &bufferInfo;
	writeDescriptorSet[0].pImageInfo = NULL;
	writeDescriptorSet[0].pTexelBufferView = NULL;

	writeDescriptorSet[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	writeDescriptorSet[1].pNext = NULL;
	writeDescriptorSet[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	writeDescriptorSet[1].descriptorCount = 1;
	writeDescriptorSet[1].dstSet = descriptorSet;
	writeDescriptorSet[1].dstBinding = 1;
	writeDescriptorSet[1].dstArrayElement = 0;
	writeDescriptorSet[1].pBufferInfo = NULL;
	writeDescriptorSet[1].pImageInfo = &imageInfo;
	writeDescriptorSet[1].pTexelBufferView = NULL;

	vkUpdateDescriptorSets(vulkan_logical_device, 2, writeDescriptorSet, 0, NULL);
}
