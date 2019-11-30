#ifndef SHADER_MODULE_H
#define SHADER_MODULE_H

#include "shaderc/shaderc.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

#define SHADERC_VERTEX_SHADER shaderc_glsl_vertex_shader
#define SHADERC_FRAGMENT_SHADER shaderc_glsl_fragment_shader


void compileShader(const char* shader_name, const uint32_t shader_size, const char* shader_code, const shaderc_shader_kind shader_type, uint32_t* compiled_size, uint32_t** compiled_code);


#ifdef __cplusplus
}
#endif // __cplusplus
#endif // !SHADER_MODULE_H
