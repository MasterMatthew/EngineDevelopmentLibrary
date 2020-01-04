#ifndef GLFW_MODULE_H
#define GLFW_MODULE_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

//inline void initWindow();

//inline void windowHint();

void createWindow(int width, int height, char* title);
void* getWindowHandle();

int getKeyPressed(int key);
int getKeyReleased(int key);

const char** getRequiredExtensions(uint32_t* count);

int windowShouldClose();
void pollEvents();

#ifdef __cplusplus
}
#endif //__cplusplus
#endif // !GLFW_MODULE_H
