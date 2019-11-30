#include "io_module.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif // !STB_IMAGE_IMPLEMENTATION

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "cglm/cglm.h"

//Basic file loader
int loadFile(const char* filename, int* size, char** data) {
	FILE* file = fopen(filename, "rb"); //Open the file
	if (!file) {
		fprintf(stderr, "File failed to open: %d\n", errno);
		//printf("Error: ", strerror(errno));
		*data = NULL;
		return IO_FAILED;
	}

	fseek(file, 0, SEEK_END);	//Move cursor to end of file
	*size = ftell(file);		//Get the total size of the file
	fseek(file, 0, SEEK_SET);	//Move cursor to beginning of file

	*data = malloc(*size + 1);	//Allocate memory to hold file

	int result = fread(*data, sizeof(char), *size, file);
	if (result != *size) {
		free(*data);
		*data = NULL;
		*size = 0;
		fprintf(stderr, "Failed to read file: %s\n", filename);
		return IO_FAILED;
	}

	(*data)[*size] = 0; //Add a null-terminator for strings

	if (fclose(file) == EOF) {
		fprintf(stderr, "Failed to close file: %s\n", filename); //Close the file
		return IO_FAILED;
	}
	return IO_SUCCESS;
}

//Simple STBI abstraction function
int loadImage(const char* filename, int* width, int* height, int* channels, unsigned char** data) {
	//TODO: Ideally images should be loaded directly into a mapped memory address to skip a memcpy
	*data = stbi_load(filename, width, height, channels, STBI_rgb_alpha);
	if (!*data) {
		fprintf(stderr, "Failed to load image!\n");
		return IO_FAILED;
	}
	return IO_SUCCESS;
}

void freeImage(unsigned char* data) {
	stbi_image_free(data);
}

//Assimp wrapper function with processing
//Loads an entire scene into the VertexBufferCreateInfo pointer
//Ideally this can be done more efficiently
int loadModel(const char* filename, uint32_t* numMeshes, VertexBufferCreateInfo** vertexBufferCreateInfo) {
	//aiScene scene = aiImportFile();

	struct aiScene* scene = aiImportFile(filename,
		//aiProcess_Triangulate | 
		//aiProcess_JoinIdenticalVertices | 
		//aiProcess_SortByPType
		NULL
	);

	if (!scene) {
		printf("Failed to load scene!\n");
		printf(aiGetErrorString());
		return IO_FAILED;
	}

	*numMeshes = scene->mNumMeshes;
	printf("Num Meshes %d\n", *numMeshes);

	VertexBufferCreateInfo* createInfo = (*vertexBufferCreateInfo) = malloc(*numMeshes * sizeof(VertexBufferCreateInfo));

	for (int i = 0; i < *numMeshes; i++) {
		struct aiMesh* mesh = scene->mMeshes[i];
		//VertexBufferCreateInfo createInfo = createInfos[i];

		int numVertices = mesh->mNumVertices;
		int numIndices = mesh->mNumFaces;
		
		createInfo->verticesCount = numVertices;
		createInfo->indicesCount = numIndices * 3;
		createInfo->attributeCount = 3;
		createInfo->pAttributeSizes = (uint32_t[]) { sizeof(vec3), sizeof(vec3), sizeof(vec2) };

		printf("Num Vertices: %d\n", numVertices);

		uint32_t* indices = createInfo->pIndices = malloc(numIndices * 3 * sizeof(int));
		for (int j = 0; j < numIndices; j++) {
			unsigned int* face = mesh->mFaces[j].mIndices;
			indices[j * 3 + 0] = face[0];
			indices[j * 3 + 1] = face[1];
			indices[j * 3 + 2] = face[2];
			//printf("%d, %d, %d\n", face[0], face[1], face[2]);
		}

		float* vertices = createInfo->pVertices = malloc(numVertices * (sizeof(vec3) + sizeof(vec3) + sizeof(vec2)));

		int normalOffset = numVertices * 3;
		int texCoordOffset = normalOffset + numVertices * 3;

		for (int j = 0; j < numVertices; j++) {
			struct aiVector3D vertex = mesh->mVertices[j];
			//struct aiVector3D normal = mesh->mNormals[j];
			//struct aiVector3D texCoord = mesh->mTextureCoords[0][j];

			vertices[j * 3 + 0] = vertex.x;
			vertices[j * 3 + 1] = vertex.y;
			vertices[j * 3 + 2] = vertex.z;

			vertices[j * 3 + 0 + normalOffset] = 0;// normal.x;
			vertices[j * 3 + 1 + normalOffset] = 0;// normal.y;
			vertices[j * 3 + 2 + normalOffset] = 0;// normal.z;

			vertices[j * 2 + 0 + texCoordOffset] = 0;// texCoord.x;
			vertices[j * 2 + 1 + texCoordOffset] = 0;// texCoord.y;
		}

		createInfo++;
	}

	printf("Scene loaded: %s\n", filename);
	aiReleaseImport(scene);
	return IO_SUCCESS;
}
