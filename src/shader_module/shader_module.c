#include "shader_module.h"


//Compiles shaders using shaderc
void compileShader(const char* shader_name, const uint32_t shader_size, const char* shader_code, const shaderc_shader_kind shader_type, uint32_t* compiled_size, uint32_t** compiled_code) {
	shaderc_compiler_t compiler = shaderc_compiler_initialize();
	shaderc_compile_options_t options = shaderc_compile_options_initialize();

	shaderc_compile_options_set_source_language(options, shaderc_source_language_glsl);
	shaderc_compile_options_set_generate_debug_info(options);
	shaderc_compile_options_set_target_env(options, shaderc_target_env_vulkan, shaderc_env_version_vulkan_1_0);

	shaderc_compilation_result_t result = shaderc_compile_into_spv(compiler, shader_code, shader_size, shader_type, shader_name, "main", options);
	shaderc_compilation_status status = shaderc_result_get_compilation_status(result);

	switch (status) {
	case shaderc_compilation_status_success:
		printf("Shader compiled successfully: %s\n", shader_name);
		break;
	case shaderc_compilation_status_compilation_error:
		printf("Shader compilation error: %s\n", shader_name);
		break;
	default:
		printf("Shader unknown error: %s\n", shader_name);
		break;
	}
	if (status != shaderc_compilation_status_success) {
		printf(shaderc_result_get_error_message(result));
	}

	*compiled_size = shaderc_result_get_length(result);
	*compiled_code = malloc(*compiled_size * sizeof(uint32_t));
	memcpy(*compiled_code, shaderc_result_get_bytes(result), *compiled_size);

	shaderc_result_release(result);
	shaderc_compile_options_release(options);
	shaderc_compiler_release(compiler);
}