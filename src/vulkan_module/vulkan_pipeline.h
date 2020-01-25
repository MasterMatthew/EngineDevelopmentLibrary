/*
This file contains all functionality related to vulkan pipelines
*/
#ifndef VULKAN_PIPELINE_H
#define VULKAN_PIPELINE_H

#include "vulkan/vulkan.h"


/**
Creates a renderpass

@param renderpass A pointer to the created renderpass
*/
void createRenderpass(VkRenderPass* renderpass);

/**
Destroys a renderpass

@param renderpass The renderpass to be destroyed
*/
void destroyRenderpass(VkRenderPass renderpass);

/**
Creates a shader module from SPIR-V code

@param size Size of the code
@param code Code of the shader
@param shaderModule Pointer to the created shader module
*/
void createShaderModule(const uint32_t size, const uint32_t* code, VkShaderModule* shaderModule);

/**
Creates a pipeline layout

@param setLayoutCount The number of descriptor set layouts used by the pipeline layout
@param pSetLayouts Array of descriptor set layouts to be used by the pipeline layout
@param layout Pointer to the created pipeline layout
*/
void createPipelineLayout(const uint32_t setLayoutCount, const VkDescriptorSetLayout* pSetLayouts, VkPipelineLayout* layout);
/**
Destroy a pipeline layout

@param pipelineLayout The pipeline layout to be destroyed
*/
void destroyPipelineLayout(VkPipelineLayout pipelineLayout);

/**
Create a graphics pipeline

@param shaders Array of shader modules to be used by the pipeline
@param layout Pipeline layout to be used by the pipeline
@param renderpass Renderpass to be used by the pipeline
@param pipeline Pointer to the created pipeline
*/
void createPipeline(VkShaderModule* shaders, VkPipelineLayout layout, VkRenderPass renderpass, VkPipeline* pipeline);
/**
Destroy a graphics pipeline

@param pipeline The pipeline to be destroyed
*/
void destroyPipeline(VkPipeline pipeline);


// CONSTANTS

// Premade input assembly state for a standard triangle list topology
static const VkPipelineInputAssemblyStateCreateInfo PIPELINE_TOPOLOGY_TRIANGLE_LIST = {
	/*.sType = */ VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
	/*.pNext = */ NULL,
	/*.flags = */ 0,
	/*.topology = */ VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
	/*.primitiveRestartEnable = */ VK_FALSE
};

#endif // !VULKAN_PIPELINE_H
