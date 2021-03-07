#include "vulkan.h"

static GLFWwindow* GLOBAL_window;
static VkInstance GLOBAL_vulkan_instance;

static GLFWwindow* _zse_rVK_windowInit(uint32_t x, uint32_t y)
{
	glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    return glfwCreateWindow(x, y, "Vulkan", NULL, NULL);
}

static void _zse_rVK_mainLoop(GLFWwindow* window)
{
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }
}

static int _zse_rVK_destroy(GLFWwindow *window)
{
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

static int _zse_rVK_createInstance()
{
	VkApplicationInfo appInfo;
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = NULL;
    appInfo.pApplicationName = "ZSE";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "ZSE";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    return 0;
}

void zse_render_vulkanInitTEST()
{
	GLOBAL_window = _zse_rVK_windowInit(1000, 800);
	_zse_rVK_mainLoop(GLOBAL_window);
	_zse_rVK_destroy(GLOBAL_window);


}


