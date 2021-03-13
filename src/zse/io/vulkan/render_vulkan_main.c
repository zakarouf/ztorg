#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
//#include <cglm/cglm.h>

#include "../../sys/sys.h"
#include "vulkan.h"

#define ZSE_CONFIG__rVK__LOG_DEBUG_ONLYSHOW_IMPORTANT_MESSAGES
//#define ZSE_CONFIG__rVK__MINIATURE
#define ZSE_CONFIG__rVK__NDEBUG


#define ZSE_CONFIG__rVK__OVERRIDE__physicalDevice 1


#ifndef ZSE_CONFIG__rVK__MINIATURE
    #ifdef ZSE_CONFIG__rVK__NDEBUG
        const bool enableValidationLayers = false;
    #else
        const bool enableValidationLayers = true;
    #endif
#endif


#ifdef ZSE_CONFIG_LOGS__USE_VARDIC_MACROS
    #define NOTPUB_log_normal(format , ...)\
        zse_sys_log(stdout,"\x1b[38;5;3m" "rVK:" format "\x1b[0m", ##__VA_ARGS__ )

    #define NOTPUB_log_error(format , ...)\
        zse_sys_log(stdout,"\x1b[38;5;1m" "rVK:ERROR:" format "\x1b[0m", ##__VA_ARGS__ )
    #define NOTPUB_log_distinct(color ,format, ...)\
        zse_sys_log(stdout, "\x1b[38;5;%dmrVK:" format "\x1b[0m", color, ##__VA_ARGS__ )

#else
    #define NOTPUB_log_normal(...)\
        {__VA_ARGS__;}
    #define NOTPUB_log_error(...)\
        {__VA_ARGS__;}
#endif


typedef struct _zse_rvk_ts_QueueFamilyIndices {
    uint32_t graphicsFamily;
    uint32_t presentFamily;
    bool graphicsFamily_hasValue;
    bool presentFamily_hasValue;
}zse_rVK__t_QueueFamilyIndices;

static int _zse_rVK_t_QueueFamilyIndices_isComplete(zse_rVK__t_QueueFamilyIndices indices)
{
    return (indices.presentFamily_hasValue & indices.graphicsFamily_hasValue);
}


typedef struct _zse_rVK_ESSENTIAL_HANDLERS
{

    GLFWwindow*      _rVK_window;

    VkInstance       _rVK_vulkan_instance;

    VkPhysicalDevice _rVK_physicalDevice;
    VkDevice         _rVK_device;
    VkQueue          _rVK_graphicsQueue;
    VkQueue          _rVK_presentQueue;

    VkSurfaceKHR     _rVK_surface;


    VkDebugUtilsMessengerEXT _rVK_debugMessenger;

}_zse_rVK_HANDLERS;
static const int GLOBAL_rVK_validationLayersCount = 1;


static VkResult _zse_rVK_createDebugUtilsMessengerEXT
(
    VkInstance instance
    , const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo
    , const VkAllocationCallbacks* pAllocator
    , VkDebugUtilsMessengerEXT* pDebugMessenger
) {
    PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != NULL) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

static void _zse_rVK_DestroyDebugUtilsMessengerEXT
(
    VkInstance instance
    , VkDebugUtilsMessengerEXT debugMessenger
    , const VkAllocationCallbacks* pAllocator
) {
    PFN_vkDestroyDebugUtilsMessengerEXT func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != NULL) {
        func(instance, debugMessenger, pAllocator);
    }
}

#ifndef ZSE_CONFIG__rVK__MINIATURE
static bool checkValidationLayerSupport(const char *validationLayers, const int validationLayersCount) {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, NULL);

    VkLayerProperties *availableLayers = malloc(sizeof(VkLayerProperties) *layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers);


    for (int i = 0; i < layerCount; ++i)
    {
        NOTPUB_log_normal("%s\n", availableLayers[i].layerName);
    }
    free(availableLayers);
    return 0;

    #define checkValdition(val, aval)\
    {\
        bool layerFound = false;\
        for (int i = 0; i < layerCount; i++) {\
            if (strcmp(val, aval[i].layerName) == 0) {\
                    layerFound = true;\
                    break;\
            }\
        }\
        if (!layerFound) {\
                free(availableLayers);\
                return false;\
        }\
    }
    checkValdition(validationLayers, availableLayers);
    #undef checkValdition
    

    free(availableLayers);

    
    return true;
}
#endif

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

static StringLines_t _zse_rVK_getRequiredExtentions()
{
    StringLines_t extentions;

    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    extentions = z__StringLines_createEmpty(128, glfwExtensionCount+2);

    for (int i = 0; i < glfwExtensionCount; ++i)
    {
        
    }

}

static VkInstance _zse_rVK_createInstance(int *errorCode)
{

    #ifndef ZSE_CONFIG__rVK__MINIATURE
        if (enableValidationLayers && !checkValidationLayerSupport(GLOBAL_rVK_validationLayers, GLOBAL_rVK_validationLayersCount)) {
            NOTPUB_log_error(" validation layers requested, but not available!");
        }
    #endif

    VkInstance instance;

	VkApplicationInfo appInfo;
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = NULL;
    appInfo.pApplicationName = "ZSE";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "ZSE";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

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
static int zse_rVK_initVulkan(_zse_rVK_HANDLERS *Handles)
{
    int errorCode;
    
    Handles->_rVK_vulkan_instance = _zse_rVK_createInstance(&errorCode);
    _zse_rVK_setupDebugMessenger(Handles->_rVK_vulkan_instance, &Handles->_rVK_debugMessenger);

    Handles->_rVK_surface = _zse_rVK_createSurface(
          &errorCode
        , Handles->_rVK_vulkan_instance
        , Handles->_rVK_window);

    Handles->_rVK_physicalDevice = _zse_rVK_pickPhysicalDevice(
          &errorCode
        , Handles->_rVK_vulkan_instance
        , Handles->_rVK_surface
    );

    _zse_rVK_cld_createLogicalDevice(
          &errorCode
        , &Handles->_rVK_physicalDevice
        , &Handles->_rVK_device
        , &Handles->_rVK_graphicsQueue
        , &Handles->_rVK_presentQueue
        , Handles->_rVK_surface
    );

    return errorCode;
}

static void _zse_rVK_mainLoop(GLFWwindow* window)
{
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        zse_sys_msleep(100);
    }
}

static _zse_rVK_HANDLERS *_zse_rVK_initHANDLES(void)
{
    _zse_rVK_HANDLERS *h = calloc(sizeof(_zse_rVK_HANDLERS), 1);
    h->_rVK_physicalDevice = VK_NULL_HANDLE;
    h->_rVK_device = 0;
    h->_rVK_vulkan_instance = 0;
    h->_rVK_debugMessenger = 0;

    return h;
}

int zse_rVK_init(void)
{
    _zse_rVK_HANDLERS *HANDLES = _zse_rVK_initHANDLES();

    HANDLES->_rVK_window = _zse_rVK_windowInit(1000, 800);

    if(zse_rVK_initVulkan(HANDLES) != 0)
    {
        NOTPUB_log_error("CANT init Vulkan\n");
        return 1;
    };


    _zse_rVK_mainLoop(HANDLES->_rVK_window);

    _zse_rVK_destroy( 
          HANDLES->_rVK_window
        , &HANDLES->_rVK_surface
        , &HANDLES->_rVK_vulkan_instance
        , &HANDLES->_rVK_debugMessenger
        , &HANDLES->_rVK_device
    );

    return 0;
}

// undefs
#undef NOTPUB_log_normal
#undef NOTPUB_log_error
