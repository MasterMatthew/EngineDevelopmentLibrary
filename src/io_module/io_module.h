#ifndef IO_MODULE_H
#define IO_MODULE_H

#include <stdio.h>
#include <errno.h>

#include "common_struct.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

//extern int errno;

#define IO_SUCCESS 0
#define IO_FAILED 1

int loadFile(const char* filename, int* size, char** data);
int loadImage(const char* filename, int* width, int* height, int* channels, unsigned char** data);
void freeImage(unsigned char* data);

int loadModel(const char* filename, uint32_t* numMeshes, VertexBufferCreateInfo** vertexBufferCreateInfo);

#ifdef __cplusplus
}
#endif // __cplusplus
#endif / !IO_MODULE_H