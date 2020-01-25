#include "vulkan_init.h"

#include "vulkan_state.h"

#include "vulkan_debug.h"
#include "vulkan_image.h"
#include "vulkan_pipeline.h"
#include "vulkan_constant.h"
#include "vulkan_struct.h"
#include "vulkan_command_buffer.h"
#include "vulkan_memory.h"


void initVulkan(const char *applicationName, const char *engineName, const string_array &requestedLayers, const string_array &requestedExtension) {
	//Vulkan instance creation
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext = NULL;
	appInfo.pApplicationName = applicationName;
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = engineName;
	appInfo.engineVersion = VK_MAKE_VERSION(3, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_1;

	//TODO: CHECK LAYERS AND EXTENSIONS
	VkInstanceCreateInfo instanceCreateInfo = {};
	instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceCreateInfo.flags = 0;
	instanceCreateInfo.pNext = NULL;
	instanceCreateInfo.pApplicationInfo = &appInfo;
	instanceCreateInfo.enabledLayerCount = requestedLayers.stringCount;
	instanceCreateInfo.ppEnabledLayerNames = requestedLayers.pStrings;
	instanceCreateInfo.enabledExtensionCount = requestedExtension.stringCount;
	instanceCreateInfo.ppEnabledExtensionNames = requestedExtension.pStrings;

	uint32_t count;
	vkEnumerateInstanceLayerProperties(&count, NULL);
	VkLayerProperties *layerProperties = (VkLayerProperties*) malloc(count * sizeof(VkLayerProperties));
	vkEnumerateInstanceLayerProperties(&count, layerProperties);

	for (uint32_t i = 0; i < count; i++) {
		printf("%s\n", layerProperties[i].layerName);
	}

	//vkCreateInstance(&instanceCreateInfo, NULL, &instance);

	checkResult(vkCreateInstance(&instanceCreateInfo, NULL, &vulkan_instance), "Vulkan instance creation");

	//TODO: Deal with debug code
	//TODO: Validation layers go here
	

	//Vulkan Physical Device creation

	//Enumerate the physical devices
	vkEnumeratePhysicalDevices(vulkan_instance, &vulkan_physical_device_count, NULL);
	vulkan_physical_devices = (VkPhysicalDevice*) malloc(vulkan_physical_device_count * sizeof(VkPhysicalDevice));
	vkEnumeratePhysicalDevices(vulkan_instance, &vulkan_physical_device_count, vulkan_physical_devices);

	for (uint32_t i = 0; i < vulkan_physical_device_count; i++) {
		VkPhysicalDevice currentDevice = vulkan_physical_devices[i];
		VkPhysicalDeviceProperties properties;
		VkPhysicalDeviceFeatures features;
		vkGetPhysicalDeviceProperties(currentDevice, &properties);
		vkGetPhysicalDeviceFeatures(currentDevice, &features);

		if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU &&
			features.geometryShader &&
			features.samplerAnisotropy) {
			vulkan_physical_device = currentDevice;
			vulkan_physical_device_properties = properties;
			vulkan_physical_device_features = features;
			break;
		}
	}

	if (vulkan_physical_device == NULL) fprintf(stderr, "Failed to find suitable device!\n");
	else printf("Physical device found!\n");

	vkGetPhysicalDeviceMemoryProperties(vulkan_physical_device, &vulkan_physical_device_memory_properties);

	//Handle Queues
	uint32_t queueFamilyCount;
	vkGetPhysicalDeviceQueueFamilyProperties(vulkan_physical_device, &queueFamilyCount, NULL);
	VkQueueFamilyProperties *queueFamilies = (VkQueueFamilyProperties*) malloc(queueFamilyCount * sizeof(VkQueueFamilyProperties));
	vkGetPhysicalDeviceQueueFamilyProperties(vulkan_physical_device, &queueFamilyCount, queueFamilies);

	VkDeviceQueueCreateInfo *deviceQueueCreateInfo = (VkDeviceQueueCreateInfo*) malloc(queueFamilyCount * sizeof(VkDeviceQueueCreateInfo));

	float priorities[] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };

	for (uint32_t i = 0; i < queueFamilyCount; i++) {
		VkQueueFamilyProperties queueFamily = queueFamilies[i];

		deviceQueueCreateInfo[i] = {};
		deviceQueueCreateInfo[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		deviceQueueCreateInfo[i].flags = 0;
		deviceQueueCreateInfo[i].pNext = NULL;
		deviceQueueCreateInfo[i].queueFamilyIndex = i;
		deviceQueueCreateInfo[i].queueCount = queueFamily.queueCount;
		deviceQueueCreateInfo[i].pQueuePriorities = priorities;

		if (queueFamily.queueCount <= 0) continue;
		if (!(~queueFamily.queueFlags & (VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT | VK_QUEUE_TRANSFER_BIT))) {
			vulkan_graphics_family = i;
			continue;
		} if (!(~queueFamily.queueFlags & (VK_QUEUE_COMPUTE_BIT | VK_QUEUE_TRANSFER_BIT))) {
			vulkan_compute_family = i;
			continue;
		} if (!(~queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)) {
			vulkan_transfer_family = i;
		}
	}

	//Logical Device Creation
	VkDeviceCreateInfo deviceCreateInfo;
	deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceCreateInfo.flags = 0;
	deviceCreateInfo.pNext = NULL;
	deviceCreateInfo.pQueueCreateInfos = deviceQueueCreateInfo;
	deviceCreateInfo.queueCreateInfoCount = queueFamilyCount;

	deviceCreateInfo.pEnabledFeatures = &vulkan_physical_device_features;

	const char *const extensions[] = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
	deviceCreateInfo.ppEnabledExtensionNames = extensions;
	deviceCreateInfo.enabledExtensionCount = 1;

	//TODO: Fix validation
	deviceCreateInfo.ppEnabledLayerNames = requestedLayers.pStrings;// &"VK_LAYER_LUNARG_standard_validation";
	deviceCreateInfo.enabledLayerCount = requestedLayers.stringCount;

	checkResult(vkCreateDevice(vulkan_physical_device, &deviceCreateInfo, NULL, &vulkan_logical_device), "Device creation");

	//Get queues
	vulkan_graphics_count = queueFamilies[vulkan_graphics_family].queueCount;
	vulkan_graphics_queues = (VkQueue*) malloc(vulkan_graphics_count * sizeof(VkQueue));
	for (uint32_t i = 0; i < vulkan_graphics_count; i++)
		vkGetDeviceQueue(vulkan_logical_device, vulkan_graphics_family, i, &vulkan_graphics_queues[i]);

	if (vulkan_compute_family != vulkan_graphics_family) {
		vulkan_compute_count = queueFamilies[vulkan_compute_family].queueCount;
		vulkan_compute_queues = (VkQueue*) malloc(vulkan_compute_count * sizeof(VkQueue*));
		for (uint32_t i = 0; i < vulkan_compute_count; i++)
			vkGetDeviceQueue(vulkan_logical_device, vulkan_compute_family, i, &vulkan_compute_queues[i]);
	}

	if (vulkan_transfer_family != vulkan_graphics_family) {
		vulkan_transfer_count = queueFamilies[vulkan_transfer_family].queueCount;
		vulkan_transfer_queues = (VkQueue*) malloc(vulkan_transfer_count * sizeof(VkQueue*));
		for (uint32_t i = 0; i < vulkan_transfer_count; i++)
			vkGetDeviceQueue(vulkan_logical_device, vulkan_transfer_family, i, &vulkan_transfer_queues[i]);
	}

	printf("Queue's gathered!\n");
	
	//init_vulkan_memory();
}


void termVulkan() {
	//destroySurface();

	free(vulkan_graphics_queues);
	free(vulkan_compute_queues);
	free(vulkan_transfer_queues);
	printf("Queue's freed!\n");

	//term_vulkan_memory();

	vkDestroyDevice(vulkan_logical_device, NULL);
	printf("Vulkan logical device destroyed!\n");

	vkDestroyInstance(vulkan_instance, NULL);
	printf("Vulkan instance destroyed!");

}

//Framebuffer

void createFramebuffer(const uint32_t attachmentCount, const VkImageView* attachments, const VkRenderPass renderpass, VkFramebuffer* framebuffer) {
	VkFramebufferCreateInfo framebufferCreateInfo;
	framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	framebufferCreateInfo.pNext = NULL;
	framebufferCreateInfo.flags = 0;
	framebufferCreateInfo.renderPass = renderpass;
	framebufferCreateInfo.width = vulkan_swapchain_extent.width; //Make compatible with different sizes
	framebufferCreateInfo.height = vulkan_swapchain_extent.height;
	framebufferCreateInfo.layers = 1;
	framebufferCreateInfo.attachmentCount = attachmentCount;
	framebufferCreateInfo.pAttachments = attachments;

	checkResult(vkCreateFramebuffer(vulkan_logical_device, &framebufferCreateInfo, NULL, framebuffer), "Framebuffer creation");
}

/*
Creates a framebuffer for the swapchain imageview given by imageIndex
TODO: Move this functionality into swapchains
WARNING: Allocates memory!
*/
void createSwapchainFramebuffer(const VkRenderPass renderpass, const uint32_t imageIndex, VkFramebuffer* framebuffer) {
	VkFramebufferCreateInfo framebufferCreateInfo;
	framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	framebufferCreateInfo.pNext = NULL;
	framebufferCreateInfo.flags = 0;
	framebufferCreateInfo.renderPass = renderpass;
	framebufferCreateInfo.width = vulkan_swapchain_extent.width;
	framebufferCreateInfo.height = vulkan_swapchain_extent.height;
	framebufferCreateInfo.layers = 1;
	framebufferCreateInfo.attachmentCount = 1;
	framebufferCreateInfo.pAttachments = &(vulkan_swapchain_imageviews[imageIndex]);

	checkResult(vkCreateFramebuffer(vulkan_logical_device, &framebufferCreateInfo, NULL, framebuffer), "Swapchain framebuffer creation");
}




//SHADERS
//TODO: Move to shader module
void createShaderModule(const uint32_t size, const uint32_t* code, VkShaderModule* shaderModule) {
	VkShaderModuleCreateInfo shaderModuleCreateInfo = {};
	shaderModuleCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	shaderModuleCreateInfo.pNext = NULL;
	shaderModuleCreateInfo.flags = 0;
	shaderModuleCreateInfo.codeSize = size;
	shaderModuleCreateInfo.pCode = code;

	checkResult(vkCreateShaderModule(vulkan_logical_device, &shaderModuleCreateInfo, NULL, shaderModule), "Shader module creation");
}


//TODO Find a place for these
//SEMAPHORES

void createSemaphore(VkSemaphore* semaphore) {
	checkResult(vkCreateSemaphore(vulkan_logical_device, &SEMAPHORE_CREATE_INFO, NULL, semaphore), "Semaphore creation");
}

//FENCES

void createFence(VkFence* fence) {
	checkResult(vkCreateFence(vulkan_logical_device, &FENCE_CREATE_INFO, NULL, fence), "Fence creation");
}
void createSignaledFence(VkFence* fence) {
	checkResult(vkCreateFence(vulkan_logical_device, &FENCE_CREATE_INFO_SIGNALED, NULL, fence), "Fence creation");
}

//TODO: Find a place for these
//SAMPLER

void createSampler(VkSampler* sampler) {
	VkSamplerCreateInfo samplerInfo;
	samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	samplerInfo.pNext = NULL;
	samplerInfo.flags = 0;

	samplerInfo.magFilter = VK_FILTER_LINEAR;
	samplerInfo.minFilter = VK_FILTER_LINEAR;
	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;

	samplerInfo.anisotropyEnable = VK_TRUE;
	samplerInfo.maxAnisotropy = 16;

	samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
	samplerInfo.unnormalizedCoordinates = VK_FALSE;
	samplerInfo.compareEnable = VK_FALSE;
	samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;

	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	samplerInfo.mipLodBias = 0.0f;
	samplerInfo.minLod = 0.0f;
	samplerInfo.maxLod = 0.0f;


	checkResult(vkCreateSampler(vulkan_logical_device, &samplerInfo, NULL, sampler), "Sampler creation");
}




//TEMPORARY FUNCTIONS

void updateDescriptorBuffers(VkBuffer uniformBuffer, VkImageView texture, VkSampler sampler, VkDescriptorSet descriptorSet) {
	VkDescriptorBufferInfo bufferInfo;
	bufferInfo.buffer = uniformBuffer;
	bufferInfo.offset = 0;
	bufferInfo.range = sizeof(buffer_object);

	VkDescriptorImageInfo imageInfo;
	imageInfo.imageView = texture;
	imageInfo.sampler = sampler;
	imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

	VkWriteDescriptorSet *writeDescriptorSet = (VkWriteDescriptorSet*) malloc(2 * sizeof(VkWriteDescriptorSet));
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
	printf("Descriptor sets updated!\n");
}

//Temporary code
void updateUniformBuffer(VkDeviceMemory uniformBufferMemory) {
	buffer_object ubo = {};
	mat4 model = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	mat4 view = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	glm_mat4_identity(ubo.model);

	float time = (float) clock();
	vec3 rotate = { 0, 0, 1 };
	vec3 eye = { 500, 300, 500 };
	vec3 center = { 0, 0, 0 };
	vec3 up = { 0, 0, 1 };

	glm_rotate(ubo.model, time * 0.001f * glm_rad(90), rotate);
	glm_lookat(eye, center, up, ubo.view);

	glm_perspective(glm_rad(45.0f), 800 / (float)600, 0.1f, 2000, ubo.proj);
	ubo.proj[1][1] = -1;


	int size = sizeof(ubo);
	void *data;
	vkMapMemory(vulkan_logical_device, uniformBufferMemory, 0, size, 0, &data);
	memcpy(data, &ubo, size);
	vkUnmapMemory(vulkan_logical_device, uniformBufferMemory);
}


void getNextImageIndex(const VkSemaphore semaphore, uint32_t* index) {
	vkAcquireNextImageKHR(vulkan_logical_device, vulkan_swapchain, UINT64_MAX, semaphore, VK_NULL_HANDLE, index);
}