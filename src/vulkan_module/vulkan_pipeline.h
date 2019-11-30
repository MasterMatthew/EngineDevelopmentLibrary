#ifndef VULKAN_PIPELINE_H
#define VULKAN_PIPELINE_H

#include "vulkan/vulkan.h"


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


void createRenderpass(VkRenderPass* renderpass);
void destroyRenderpass(VkRenderPass renderpass);

void createShaderModule(const uint32_t size, const uint32_t* code, VkShaderModule* shaderModule);

void createPipelineLayout(const uint32_t setLayoutCount, const VkDescriptorSetLayout* pSetLayouts, VkPipelineLayout* layout);
void destroyPipelineLayout(VkPipelineLayout pipelineLayout);
void createPipeline(VkShaderModule* shaders, const VkPipelineLayout layout, const VkRenderPass renderpass, VkPipeline* pipeline);
void destroyPipeline(VkPipeline pipeline);


// CONSTANTS

static const VkPipelineInputAssemblyStateCreateInfo PIPELINE_TOPOLOGY_TRIANGLE_LIST = {
	/*.sType = */ VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
	/*.pNext = */ NULL,
	/*.flags = */ 0,
	/*.topology = */ VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
	/*.primitiveRestartEnable = */ VK_FALSE
};



#ifdef __cplusplus
}
#endif
#endif // !VULKAN_PIPELINE_H
