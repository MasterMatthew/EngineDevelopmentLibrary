#include "demo_renderer.h"

#include "stb_image.h"
//#define VULKAN_MODULE_EXPOSE_STATE
#include "vulkan_module.h"
#include "graphics_module.h"
#include "glfw_module.h"
//#include "vulkan_init.h"

const uint32_t WINDOW_WIDTH = 800;
const uint32_t WINDOW_HEIGHT = 600;

VkRenderPass renderpass;

VkDescriptorPool descriptorPool;
VkDescriptorSetLayout descriptorSetLayout;
VkDescriptorSet descriptorSet;

VkPipelineLayout pipelineLayout;
VkPipeline pipeline;

VkCommandPool commandPool;
uint32_t swapchainImageCount;
VkFramebuffer framebuffer;
VkCommandBuffer commandBuffer;

VkBuffer uniformBuffer;
VkDeviceMemory uniformMemory;

VkSemaphore imageReady, renderingComplete;

//Temporary renderer, should be moved to ther demo folder
void initRenderer() {
	createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World");

	//TODO: Deal with GLFW
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions = getRequiredExtensions(&glfwExtensionCount);

	string_array layers;
	layers.stringCount = 3;
	layers.pStrings = (char**) malloc(3 * sizeof(char*));
	layers.pStrings[2] = "VK_LAYER_KHRONOS_validation";
	layers.pStrings[1] = "VK_LAYER_LUNARG_standard_validation";
	layers.pStrings[0] = "VK_LAYER_LUNARG_vktrace";

	string_array extensions;
	extensions.stringCount = 2;
	extensions.pStrings = (char**) malloc(3 * sizeof(char*));
	extensions.pStrings[0] = VK_KHR_SURFACE_EXTENSION_NAME;
	extensions.pStrings[1] = VK_EXT_DEBUG_REPORT_EXTENSION_NAME;
	extensions.pStrings[2];

	string_array totalExtensions;
	totalExtensions.stringCount = glfwExtensionCount + 2;
	totalExtensions.pStrings = (char**) malloc((glfwExtensionCount + 2) * sizeof(char*));
	memcpy(totalExtensions.pStrings, glfwExtensions, glfwExtensionCount * sizeof(char*));
	memcpy(totalExtensions.pStrings + glfwExtensionCount, extensions.pStrings, 2 * sizeof(char*));

	

	//Initialize Vulkan
	initVulkan("Demo", "EngineDev", layers, totalExtensions);
	//Create Surface
	createSurface(WINDOW_WIDTH, WINDOW_HEIGHT, getWindowHandle(), &swapchainImageCount);
	//Create Renderpass
	createRenderpass(&renderpass);

	//Load our shaders
	VkShaderModule vert, frag;
	loadShader("res/shaders/uniform_shader.vert", SHADERC_VERTEX_SHADER, &vert);
	loadShader("res/shaders/uniform_shader.frag", SHADERC_FRAGMENT_SHADER, &frag);

	//Create a descriptor pool and allocate descriptor sets
	createDescriptorPool(&descriptorPool);
	createDescriptorSetLayout(&descriptorSetLayout);
	allocateDescriptorSet(descriptorPool, descriptorSetLayout, &descriptorSet);

	//Create pipeline and pipeline layout
	VkShaderModule shaders[] = { vert, frag };//A terribly inefficient way to do this, should be done inline but can't because c++
	createPipelineLayout(1, &descriptorSetLayout, &pipelineLayout);
	createPipeline(shaders, pipelineLayout, renderpass, &pipeline);

	//Create some command pools (Work needs to be done to create multiple)
	createGraphicsCommandPool((VkCommandPoolCreateFlagBits) 0, &commandPool);
	//createGraphicsCommandPool(VK_COMMAND_POOL_CREATE_TRANSIENT_BIT, &graphicsPool);
	//createTransferCommandPool(VK_COMMAND_POOL_CREATE_TRANSIENT_BIT, &transferPool);

	//Outdated box mesh
	/*
	uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
	uint32_t attributeSizes[] = { sizeof(vec3), sizeof(vec3), sizeof(vec2) };
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // pos 0
		0.5f, -0.5f, 0.0f,	// pos 1
		0.5f, 0.5f, 0.0f,	// pos 2
		-0.5f, 0.5f, 0.0f,	// pos 3

		0.0f, 0.0f, 0.0f,	// normal 0
		0.0f, 0.0f, 0.0f,	// normal 1
		0.0f, 0.0f, 0.0f,	// normal 2
		0.0f, 0.0f, 0.0f,	// normal 3

		1.0f, 0.0f,			// texCoord 0
		0.0f, 0.0f,			// texCoord 1
		0.0f, 1.0f,			// texCoord 2
		1.0f, 1.0f			// texCoord 3
	};


	VertexBufferCreateInfo vertexBufferCreateinfo;
	vertexBufferCreateinfo.indicesCount = 6;
	vertexBufferCreateinfo.pIndices = indices;
	vertexBufferCreateinfo.attributeCount = 3;
	vertexBufferCreateinfo.pAttributeSizes = attributeSizes;
	vertexBufferCreateinfo.verticesCount = 4;
	vertexBufferCreateinfo.pVertices = vertices;
	*/

	//load mesh
	uint32_t numMeshes;
	VertexBufferCreateInfo* scene;
	loadModel("res/models/sponza.obj", &numMeshes, &scene);

	VertexBuffer* vertexBuffers = (VertexBuffer*) malloc(numMeshes * sizeof(VertexBuffer));

	for (int i = 0; i < numMeshes; i++) {
		uint32_t attribSizes[] = { sizeof(vec3), sizeof(vec3), sizeof(vec2) };
		scene[i].pAttributeSizes = attribSizes;

		
		createVertexBuffer(commandPool, &scene[i], &vertexBuffers[i]);

	}

	createBuffer(sizeof(buffer_object), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		&uniformBuffer, &uniformMemory);

	//Texture loading
	char* filename = "res/textures/texture.jpg";
	unsigned char* pixels;
	int width, height, channels;
	VkImage image;
	VkDeviceMemory imageMemory;
	VkImageView imageview;
	int result = loadImage(filename, &width, &height, &channels, &pixels);
	if (result == IO_FAILED) {
		std::cout << "Failed to load file: " << filename << std::endl;
		return;
	}
	createTextureImage(width, height, pixels, commandPool, &image, &imageMemory);
	createTextureImageView(image, VK_FORMAT_R8G8B8A8_UNORM, &imageview);
	freeImage(pixels);

	createBuffer(sizeof(buffer_object), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
		&uniformBuffer, &uniformMemory);


	VkSampler sampler;
	createSampler(&sampler);

	updateDescriptorBuffers(uniformBuffer, imageview, sampler, descriptorSet);

	createSwapchainFramebuffer(renderpass, 0, &framebuffer);

	//Set up the command buffer
	allocateCommandBuffer(commandPool, &commandBuffer);
	checkResult(vkBeginCommandBuffer(commandBuffer, &COMMAND_BUFFER_BEGIN_INFO), "Command Buffer recording begin");

	cmdBeginRenderpass(commandBuffer, renderpass, framebuffer);

	vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);

	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSet, 0, NULL);

	for (int i = 0; i < numMeshes; i++) {
		cmdBindVertexBuffer(commandBuffer, vertexBuffers[i]);
		vkCmdDrawIndexed(commandBuffer, vertexBuffers[i].indicesCount, 1, 0, 0, 0);
	}

	vkCmdEndRenderPass(commandBuffer);

	checkResult(vkEndCommandBuffer(commandBuffer), "Command Buffer recording end");

	createSemaphore(&imageReady);
	createSemaphore(&renderingComplete);

}


void runRenderer() {
	while (!windowShouldClose()) {
		pollEvents();
		updateUniformBuffer(uniformMemory);

		uint32_t imageIndex = 0;
		//Disable double buffering
		//getNextImageIndex(imageReady, &imageIndex);

		VkPipelineStageFlags flags[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitQueue(
			1, &imageReady, flags,
			1, &renderingComplete,
			1, &commandBuffer, NULL);

		presentQueue(1, &renderingComplete, &imageIndex);

	}
}

void termRenderer() {

	/*
	destroyPipelineLayout(pipelineLayout);
	destroyPipeline(pipeline);

	destroyDescriptorSetLayout(descriptorSetLayout);
	destroyDescriptorPool(descriptorPool);

	destroyRenderpass(renderpass);
	//destroySurface();
	termVulkan();
	glfwDestroyWindow(window);
	glfwTerminate();
	*/
}