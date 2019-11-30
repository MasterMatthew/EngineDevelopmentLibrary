#ifndef COMMON_STRUCT_H
#define COMMON_STRUCT_H

#include <stdint.h>

#ifdef __cplusplus
//extern "C" {
#endif // __cplusplus

//Simple structures that will be used in library functions

typedef struct string_array {
	uint32_t stringCount;
	char** pStrings;
} string_array;

typedef struct VertexBufferCreateInfo {
	uint32_t indicesCount;
	uint32_t* pIndices;
	uint32_t attributeCount;
	uint32_t* pAttributeSizes;
	uint32_t verticesCount;
	float* pVertices;
} VertexBufferCreateInfo;

#ifdef __cplusplus
//}
#endif // __cplusplus
#endif // !COMMON_STRUCT_H
