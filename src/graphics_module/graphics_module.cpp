#include "graphics_module.h"

void loadShader(const char* filename, const shaderc_shader_kind shaderType, VkShaderModule *shaderModule) {
	int size;
	char* code;
	uint32_t compiledSize;
	uint32_t *compiledCode;

	int result = loadFile(filename, &size, &code);
	if (result == IO_FAILED) {
		printf("Failed to load shader: %s\n", filename);
		return;
	}
	compileShader(filename, size, code, shaderType, &compiledSize, &compiledCode);
	createShaderModule(compiledSize, compiledCode, shaderModule);
}