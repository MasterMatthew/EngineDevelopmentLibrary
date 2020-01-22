#include "vulkan_pipeline.h"

#include "cglm/cglm.h"

#include "vulkan_state.h"
#include "vulkan_debug.h"

void createRenderpass(VkRenderPass *renderpass) {
	VkAttachmentDescription colorAttachment;
	colorAttachment.flags = 0;
	colorAttachment.format = vulkan_surface_format.format;
	colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
	colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

	VkAttachmentReference colorAttachmentRef;
	colorAttachmentRef.attachment = 0;
	colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpass;
	subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
	subpass.colorAttachmentCount = 1;
	subpass.pColorAttachments = &colorAttachmentRef;
	subpass.flags = 0;
	subpass.inputAttachmentCount = 0;
	subpass.pInputAttachments = NULL;
	subpass.preserveAttachmentCount = 0;
	subpass.pPreserveAttachments = NULL;
	subpass.pResolveAttachments = NULL;
	subpass.pDepthStencilAttachment = NULL;

	VkSubpassDependency dependency;
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;
	dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.srcAccessMask = 0;
	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
	dependency.dependencyFlags = 0;

	VkRenderPassCreateInfo renderPassInfo;
	renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassInfo.pNext = NULL;
	renderPassInfo.flags = 0;
	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &colorAttachment;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &subpass;
	renderPassInfo.dependencyCount = 1;
	renderPassInfo.pDependencies = &dependency;

	checkResult(vkCreateRenderPass(vulkan_logical_device, &renderPassInfo, NULL, renderpass), "RenderPass creation");
}
void destroyRenderpass(VkRenderPass renderpass) {
	vkDestroyRenderPass(vulkan_logical_device, renderpass, NULL);
}

//TODO: add descriptors and push constants
void createPipelineLayout(const uint32_t setLayoutCount, const VkDescriptorSetLayout* pSetLayouts, VkPipelineLayout* layout) {
	VkPipelineLayoutCreateInfo pipelineLayoutInfo;
	pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutInfo.pNext = NULL;
	pipelineLayoutInfo.flags = 0;
	pipelineLayoutInfo.setLayoutCount = setLayoutCount;
	pipelineLayoutInfo.pSetLayouts = pSetLayouts;
	pipelineLayoutInfo.pushConstantRangeCount = 0;
	pipelineLayoutInfo.pPushConstantRanges = NULL;

	checkResult(vkCreatePipelineLayout(vulkan_logical_device, &pipelineLayoutInfo, NULL, layout), "Pipeline layout creation");
}

void destroyPipelineLayout(VkPipelineLayout pipelineLayout) {
	vkDestroyPipelineLayout(vulkan_logical_device, pipelineLayout, NULL);
}

//These will be changed
void createPipeline(VkShaderModule* shaders, VkPipelineLayout layout, VkRenderPass renderpass, VkPipeline* pipeline) {
	VkPipelineShaderStageCreateInfo shaderStageCreateInfo[] = {{
		VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		NULL,
		0,
		VK_SHADER_STAGE_VERTEX_BIT,
		shaders[0],
		"main",
		NULL
	}, {
		VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
		NULL,
		0,
		VK_SHADER_STAGE_FRAGMENT_BIT,
		shaders[1],
		"main",
		NULL
	}};

	VkVertexInputBindingDescription *bindingDescription = (VkVertexInputBindingDescription *) malloc(3 * sizeof(VkVertexInputBindingDescription));
	bindingDescription[0].binding = 0;
	bindingDescription[0].stride = sizeof(vec3);
	bindingDescription[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	bindingDescription[1].binding = 1;
	bindingDescription[1].stride = sizeof(vec3);
	bindingDescription[1].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	bindingDescription[2].binding = 2;
	bindingDescription[2].stride = sizeof(vec2);
	bindingDescription[2].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	VkVertexInputAttributeDescription *attributeDescription = (VkVertexInputAttributeDescription *) malloc(3 * sizeof(VkVertexInputAttributeDescription));
	attributeDescription[0].binding = 0;
	attributeDescription[0].format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescription[0].location = 0;
	attributeDescription[0].offset = 0;// offsetof(vertex, pos);

	attributeDescription[1].binding = 1;
	attributeDescription[1].format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescription[1].location = 1;
	attributeDescription[1].offset = 0;// offsetof(vertex, normal); //Might be align 4

	attributeDescription[2].binding = 2;
	attributeDescription[2].format = VK_FORMAT_R32G32_SFLOAT;
	attributeDescription[2].location = 2;
	attributeDescription[2].offset = 0;// offsetof(vertex, texCoord);

	VkPipelineVertexInputStateCreateInfo inputInfo = {};
	inputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	inputInfo.pNext = NULL;
	inputInfo.flags = 0;
	inputInfo.vertexBindingDescriptionCount = 3;
	inputInfo.pVertexBindingDescriptions = bindingDescription;
	inputInfo.vertexAttributeDescriptionCount = 3;
	inputInfo.pVertexAttributeDescriptions = attributeDescription;

	VkViewport viewport = {
		0.0f, 0.0f,
		vulkan_swapchain_extent.width, //Change to support buffers of different sizes
		vulkan_swapchain_extent.height,
		0.0f, 1.0f
	};

	VkRect2D scissor;
	scissor.offset = { 0, 0 };
	scissor.extent = vulkan_swapchain_extent;

	VkPipelineViewportStateCreateInfo viewportInfo;
	viewportInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportInfo.pNext = NULL;
	viewportInfo.flags = 0;
	viewportInfo.viewportCount = 1;
	viewportInfo.pViewports = &viewport;
	viewportInfo.scissorCount = 1;
	viewportInfo.pScissors = &scissor;

	VkPipelineRasterizationStateCreateInfo rasterInfo;
	rasterInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterInfo.pNext = NULL;
	rasterInfo.flags = 0;
	rasterInfo.depthClampEnable = VK_FALSE; //Clamps fragments outside of near/far instead of discarding
	rasterInfo.rasterizerDiscardEnable = VK_FALSE; //From lunarg, "controls whether primitives are discarded immediately before the rasterization stage"
	rasterInfo.polygonMode = VK_POLYGON_MODE_FILL;
	rasterInfo.lineWidth = 1.0f;
	rasterInfo.cullMode = VK_CULL_MODE_BACK_BIT;
	//rasterInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
	rasterInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	rasterInfo.depthBiasEnable = VK_FALSE;
	rasterInfo.depthBiasConstantFactor = 0.0f;
	rasterInfo.depthBiasClamp = 0.0f;
	rasterInfo.depthBiasSlopeFactor = 0.0f;

	VkPipelineMultisampleStateCreateInfo multisampleInfo;
	multisampleInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisampleInfo.pNext = NULL;
	multisampleInfo.flags = 0;
	multisampleInfo.sampleShadingEnable = VK_FALSE;
	multisampleInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
	multisampleInfo.minSampleShading = 1.0f;
	multisampleInfo.pSampleMask = NULL;
	multisampleInfo.alphaToCoverageEnable = VK_FALSE;
	multisampleInfo.alphaToOneEnable = VK_FALSE;

	VkPipelineColorBlendAttachmentState colorBlendAttachmentState;
	colorBlendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	colorBlendAttachmentState.blendEnable = VK_FALSE;
	colorBlendAttachmentState.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
	colorBlendAttachmentState.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachmentState.colorBlendOp = VK_BLEND_OP_ADD;
	colorBlendAttachmentState.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	colorBlendAttachmentState.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachmentState.alphaBlendOp = VK_BLEND_OP_ADD;

	VkPipelineColorBlendStateCreateInfo colorBlendInfo;
	colorBlendInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlendInfo.pNext = NULL;
	colorBlendInfo.flags = 0;
	colorBlendInfo.logicOpEnable = VK_FALSE;
	colorBlendInfo.logicOp = VK_LOGIC_OP_COPY;
	colorBlendInfo.attachmentCount = 1;
	colorBlendInfo.pAttachments = &colorBlendAttachmentState;
	colorBlendInfo.blendConstants[0] = 0.0f;
	colorBlendInfo.blendConstants[1] = 0.0f;
	colorBlendInfo.blendConstants[2] = 0.0f;
	colorBlendInfo.blendConstants[3] = 0.0f;

	//Dynamic state nonsense

	VkGraphicsPipelineCreateInfo pipelineInfo;
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.pNext = NULL;
	pipelineInfo.flags = 0;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStageCreateInfo;

	pipelineInfo.pVertexInputState = &inputInfo;
	pipelineInfo.pInputAssemblyState = &PIPELINE_TOPOLOGY_TRIANGLE_LIST;
	pipelineInfo.pViewportState = &viewportInfo;
	pipelineInfo.pRasterizationState = &rasterInfo;
	pipelineInfo.pMultisampleState = &multisampleInfo;
	pipelineInfo.pDepthStencilState = NULL;
	pipelineInfo.pColorBlendState = &colorBlendInfo;
	pipelineInfo.pDynamicState = NULL;

	pipelineInfo.layout = layout;
	pipelineInfo.renderPass = renderpass;
	pipelineInfo.subpass = 0;

	pipelineInfo.basePipelineHandle = NULL;
	pipelineInfo.basePipelineIndex = -1;
	pipelineInfo.pTessellationState = NULL;

	checkResult(vkCreateGraphicsPipelines(vulkan_logical_device, NULL, 1, &pipelineInfo, NULL, pipeline), "Graphics pipeline creation");
}

void destroyPipeline(VkPipeline pipeline) {
	vkDestroyPipeline(vulkan_logical_device, pipeline, NULL);
}