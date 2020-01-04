#include "glfw_module.h"


#ifdef WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"
#else
#include "GLFW/glfw3.h"
#endif

#include "glfw_defines.h"

GLFWwindow* window;

void createWindow(int width, int height, char* title) {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(width, height, title, NULL, NULL);
}

void* getWindowHandle() {
#ifdef WIN32
	return glfwGetWin32Window(window);
#endif
}

int getKeyPressed(int key) {
	return glfwGetKey(window, key) == GLFW_PRESS;
}
int getKeyReleased(int key) {
	return glfwGetKey(window, key) == GLFW_RELEASE;
}

const char** getRequiredExtensions(uint32_t* count) {
	return glfwGetRequiredInstanceExtensions(count);
}

int windowShouldClose() { return glfwWindowShouldClose(window); }
void pollEvents() { glfwPollEvents(); }