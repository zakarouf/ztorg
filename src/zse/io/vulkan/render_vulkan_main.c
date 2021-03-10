#include <stdlib.h>
#include <time.h>

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>


#include "../../sys/sys.h"

#include "vulkan.h"

#define NOTPUB_log_normal(format , ...)\
    zse_sys_log(stdout,"rVK:" format, ##__VA_ARGS__ )

#define NOTPUB_log_error(format , ...)\
    zse_sys_log(stderr,"rVK:ERROR" format, ##__VA_ARGS__ )

static GLFWwindow* GLOBAL_window;
static VkInstance GLOBAL_vulkan_instance;

static GLFWwindow* _zse_rVK_windowInit(uint32_t x, uint32_t y)
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    return glfwCreateWindow(x, y, "ZSE", NULL, NULL);
}

static int _zse_rVK_destroy(GLFWwindow *window, VkInstance instance)
{
    vkDestroyInstance(instance, NULL);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

static VkInstance _zse_rVK_createInstance(int *errorCode)
{
    VkInstance instance;

	VkApplicationInfo appInfo;
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = NULL;
    appInfo.pApplicationName = "ZSE";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "ZSE";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_2;

    VkInstanceCreateInfo createInfo;
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;


    // Extentions
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;


    // Get Vulkan Instance Info
    createInfo.enabledLayerCount = 0;
    if(vkCreateInstance(&createInfo, NULL, &instance) != VK_SUCCESS)
        *errorCode = 1;

    uint32_t extensionCount;
    vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);

    VkExtensionProperties *Extentions;
    if ((Extentions = malloc(sizeof(VkExtensionProperties) * extensionCount)) != NULL)
    {
        *errorCode = 4;
    }

    // LOG Extentions
    vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, Extentions);
    NOTPUB_log_normal("rVK:Extentions Avaliable >>\n");
    for (int i = 0; i < extensionCount; ++i)
    {
        NOTPUB_log_normal("\t\t%s\n", Extentions[i].extensionName);
    }

    *errorCode = 0;

    return instance;
}

int zse_rVK_initVulkan()
{
    int errorCode;
    GLOBAL_window = _zse_rVK_windowInit(1000, 800);
    GLOBAL_vulkan_instance = _zse_rVK_createInstance(&errorCode);

    return errorCode;
}

static void _zse_rVK_mainLoop(GLFWwindow* window)
{
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        zse_sys_msleep(100);
    }
}

void zse_render_vulkanInitTEST()
{
	if(zse_rVK_initVulkan() != 0)
    {
        NOTPUB_log_error("CANT init Vulkan\n");
    };

	_zse_rVK_mainLoop(GLOBAL_window);

	_zse_rVK_destroy(GLOBAL_window, GLOBAL_vulkan_instance);

}

// undefs
#undef NOTPUB_log_normal
