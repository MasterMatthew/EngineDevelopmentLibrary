#ifndef GRAPHICS_MODULE_H
#define GRAPHICS_MODULE_H

#include "vulkan_module.h"
#include "shader_module.h"
#include "io_module.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void loadShader(const char* shader_filename, const shaderc_shader_kind shader_type, VkShaderModule* shader);


#ifdef __cplusplus
}
#endif // __cplusplus
#endif // !GRAPHICS_MODULE_H
