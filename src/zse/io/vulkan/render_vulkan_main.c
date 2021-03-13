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
        zse_sys_log(stdout, "\x1b[38;5;%dm" "rVK:" format "\x1b[0m", color, ##__VA_ARGS__ )

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

static const char *GLOBAL_rVK_validationLayers = {"VK_LAYER_KHRONOS_validation"};
static const int GLOBAL_rVK_validationLayersCount = 1;

static StringLines_t GLOBAL_rVK_deviceExtensions;

static void _zse_rVK_init_deviceExtentions(StringLines_t *dE)
{
    int device = 1;
    *dE = z__StringLines_createEmpty(96, device);
    z__StringLines_pushString(dE, 96, VK_KHR_SWAPCHAIN_EXTENSION_NAME);
}

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
static bool _zse_rVK_DEBUG_checkValidationLayerSupport(const char *validationLayers, const int validationLayersCount) {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, NULL);

    VkLayerProperties *availableLayers = malloc(sizeof(VkLayerProperties) *layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers);


    for (int i = 0; i < layerCount; ++i)
    {
        NOTPUB_log_normal(" LAYER AVALIABLE :> %s\n", availableLayers[i].layerName);
    }

    #define checkValdition(val, aval)\
    {\
        bool layerFound = false;\
        for (int i = 0; i < layerCount; i++) {\
            if (strcmp(val, aval[i].layerName) == 0) {\
                    layerFound = true;\
                    NOTPUB_log_normal(" ValidationLayer Found\n");\
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

static VKAPI_ATTR VkBool32 VKAPI_CALL _zse_rVK_debugCallback
(
      VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity
    , VkDebugUtilsMessageTypeFlagsEXT messageType
    , const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData
    , void* pUserData) 
{

    
    #ifndef ZSE_CONFIG__rVK__LOG_DEBUG_ONLYSHOW_IMPORTANT_MESSAGES
        if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
            NOTPUB_log_distinct(1 ,":ValidationLayer:ERROR: %s\n", pCallbackData->pMessage);
        }
        else
        {
            NOTPUB_log_distinct(8 ,":ValidationLayer: %s\n", pCallbackData->pMessage);
        }
    #else
        if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
            NOTPUB_log_distinct(1 ,":ValidationLayer: %s\n", pCallbackData->pMessage);
        }
    #endif

    return VK_FALSE;
}

static void _zse_rVK__populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT* createInfo) {

    createInfo->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo->messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo->messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo->pfnUserCallback = _zse_rVK_debugCallback;
    createInfo->pUserData = NULL;
}


static void _zse_rVK_setupDebugMessenger(VkInstance instance, VkDebugUtilsMessengerEXT *debugMessenger)
{
    if (!enableValidationLayers) 
        return;

    VkDebugUtilsMessengerCreateInfoEXT createInfo = {0};
    _zse_rVK__populateDebugMessengerCreateInfo(&createInfo);

    if ( _zse_rVK_createDebugUtilsMessengerEXT(instance, &createInfo, NULL, debugMessenger) != VK_SUCCESS) {
        NOTPUB_log_error("Failed To Set Up Debug Messenger!");
    }
}

static zse_rVK__t_QueueFamilyIndices _zse_rVK__phd_findQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
static void _zse_rVK_cld_createLogicalDevice
(
      int *errorCode
    , VkPhysicalDevice *physicalDevice
    , VkDevice *device
    , VkQueue *graphicsQueue
    , VkQueue *presentQueue
    , VkSurfaceKHR surface
)
{
    zse_rVK__t_QueueFamilyIndices indices = _zse_rVK__phd_findQueueFamilies(*physicalDevice, surface);


    uint32_t uniqueQueueFamiliesUsed = 0;
    //uint32_t uniqueQueueFamiliesSize = 2;
    uint32_t uniqueQueueFamilies[2];
    
    if (indices.presentFamily == indices.graphicsFamily)
    {
        uniqueQueueFamiliesUsed = 1;
        uniqueQueueFamilies[0] = indices.presentFamily;
        NOTPUB_log_normal(":createLogicalDevice:Using Same `presentFamily`:%d and `graphicsFamily`:%d\n", indices.presentFamily, indices.graphicsFamily);
    } else {
        uniqueQueueFamiliesUsed = 2;
        uniqueQueueFamilies[0] = indices.presentFamily;
        uniqueQueueFamilies[1] = indices.graphicsFamily;
        NOTPUB_log_normal(":createLogicalDevice:Using Different `presentFamily`:%d and `graphicsFamily`:%d\n", indices.presentFamily, indices.graphicsFamily);
    }
    

    VkDeviceQueueCreateInfo *queueCreateInfos = calloc(sizeof(VkDeviceQueueCreateInfo) , uniqueQueueFamiliesUsed);

    float queuePriority = 1.0f;
    for (int i = 0; i < uniqueQueueFamiliesUsed; ++i)
    {
        queueCreateInfos[i].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfos[i].queueFamilyIndex = uniqueQueueFamilies[i];
        queueCreateInfos[i].queueCount = 1;
        queueCreateInfos[i].pQueuePriorities = &queuePriority;
    }



    VkPhysicalDeviceFeatures deviceFeatures = {0};

    VkDeviceCreateInfo createInfo = {0};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    createInfo.queueCreateInfoCount = uniqueQueueFamiliesUsed;
    createInfo.pQueueCreateInfos = queueCreateInfos;

    createInfo.pEnabledFeatures = &deviceFeatures;


    createInfo.enabledExtensionCount = 0;

    if (enableValidationLayers) {
        createInfo.enabledLayerCount = GLOBAL_rVK_validationLayersCount;
        createInfo.ppEnabledLayerNames = &GLOBAL_rVK_validationLayers;
    } else {
        createInfo.enabledLayerCount = 0;
    }

    if (vkCreateDevice(*physicalDevice, &createInfo, NULL, device) != VK_SUCCESS) {
        NOTPUB_log_error("Failed to create logical device!");
    }

    vkGetDeviceQueue(*device, indices.graphicsFamily, 0, graphicsQueue);
    vkGetDeviceQueue(*device, indices.presentFamily, 0, presentQueue);

}


static zse_rVK__t_QueueFamilyIndices _zse_rVK__phd_findQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
{
    zse_rVK__t_QueueFamilyIndices indices = {0};
    
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, NULL);

    VkQueueFamilyProperties *queueFamilies = malloc(sizeof(VkQueueFamilyProperties) * queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies);

    
    for (int i = 0; (i < queueFamilyCount) || !_zse_rVK_t_QueueFamilyIndices_isComplete(indices); ++i)
    {
        if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            indices.graphicsFamily = i;
            indices.graphicsFamily_hasValue = true;
        }

        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, surface, &presentSupport);

        if (presentSupport)
        {
            indices.presentFamily = i;
            indices.presentFamily_hasValue = true;
        }

    }

    free(queueFamilies);
    return indices;
}

static bool _zse_rVK__phd_checkDeviceExtensionSupport(VkPhysicalDevice device) {

    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, NULL);

    VkExtensionProperties * availableExtensions = calloc(sizeof(VkExtensionProperties) ,extensionCount);
    vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, availableExtensions);


    StringLines_t requiredExtensions = z__StringLines_createEmpty(96, GLOBAL_rVK_deviceExtensions.lines);
    for (int i = 0; i < GLOBAL_rVK_validationLayersCount; ++i)
    {
        z__StringLines_pushString(&requiredExtensions, 96, GLOBAL_rVK_deviceExtensions.data[i]);
    }

    const uint32_t TotalExtentionsRequired = requiredExtensions.linesUsed;
    uint32_t ExtentionsFound = 0;

    for (int i = 0; i < extensionCount; ++i)
    {
        for (int j = 0; j < TotalExtentionsRequired; ++j)
        {
            if (strncmp(requiredExtensions.data[j], availableExtensions[i].extensionName, 96) == 0)
            {
                ExtentionsFound += 1;
            }
        }
    }


    free (availableExtensions);
    z__StringLines_delete(&requiredExtensions);

    return TotalExtentionsRequired & ExtentionsFound;    
}

static int _zse_rVK__phd_isPhysicalDeviceSuitableForVulkan(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
{
    zse_rVK__t_QueueFamilyIndices indices = _zse_rVK__phd_findQueueFamilies(physicalDevice, surface);

    int extensionsSupported = _zse_rVK__phd_checkDeviceExtensionSupport(physicalDevice);
    int indiceComplete = _zse_rVK_t_QueueFamilyIndices_isComplete(indices);

    if (extensionsSupported  && indiceComplete){
        NOTPUB_log_normal("Physical Device is Suitable For Vulkan\n");
        return true;
    }
    else{
        NOTPUB_log_error("Physical Device is NOT Suitable For Vulkan\n");
        return false;
    }
    
}

static VkPhysicalDevice _zse_rVK_pickPhysicalDevice(int *errorCode, VkInstance instance, VkSurfaceKHR surface)
{
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);

    if (deviceCount == 0)
    {
        NOTPUB_log_error(":PhysicalDevice: Failed To Get GPU with Vulkan Support\n");
        *errorCode = -1;
        return physicalDevice;
    }

    VkPhysicalDevice *devices = calloc(sizeof(VkPhysicalDevice), deviceCount);
    vkEnumeratePhysicalDevices(instance, &deviceCount, devices);

    
    // Fillter out devices
    for (int i = 0; i < deviceCount; ++i)
    {
        
        if (_zse_rVK__phd_isPhysicalDeviceSuitableForVulkan(devices[i], surface))
        {
            //NOTPUB_log_error("AS");
            physicalDevice = devices[i];
            break;
        }
        
        
    }
    if (physicalDevice == VK_NULL_HANDLE) {
        NOTPUB_log_error(":PhysicalDevice: Failed To Get GPU with Suitable Requirements\n");
        *errorCode = -1;
    }

    return physicalDevice;

}


static StringLines_t _zse_rVK_getRequiredExtentions()
{

    StringLines_t strLines = z__StringLines_createEmpty(32, 5);

    // Extentions
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    for (int i = 0; i < glfwExtensionCount; ++i)
    {
        strcpy(strLines.data[i], glfwExtensions[i]);
        strLines.linesUsed+=1;
    }

    z__StringLines_pushString(&strLines, sizeof(VK_EXT_DEBUG_UTILS_EXTENSION_NAME), VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    NOTPUB_log_normal("%d\n", strLines.linesUsed);

    for (int i = 0; i < strLines.linesUsed; ++i)
    {
        NOTPUB_log_normal("%s\n", strLines.data[i]);        
    }

    return strLines;
}

static VkInstance _zse_rVK_createInstance(int *errorCode)
{

    #ifndef ZSE_CONFIG__rVK__MINIATURE
        if (enableValidationLayers) {
            if( !_zse_rVK_DEBUG_checkValidationLayerSupport(GLOBAL_rVK_validationLayers, GLOBAL_rVK_validationLayersCount)) {
                NOTPUB_log_error(" validation layers requested, but not available!\n");
            }
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

    VkInstanceCreateInfo createInfo = {0};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;


    

    // Extentions
    StringLines_t ExtentionsLayer = _zse_rVK_getRequiredExtentions();

    createInfo.enabledExtensionCount = ExtentionsLayer.linesUsed;
    createInfo.ppEnabledExtensionNames = (const char *const *) ExtentionsLayer.data;


    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo = {0};
    if (enableValidationLayers) 
    {
        createInfo.enabledLayerCount = GLOBAL_rVK_validationLayersCount;
        createInfo.ppEnabledLayerNames = &GLOBAL_rVK_validationLayers;

        _zse_rVK__populateDebugMessengerCreateInfo(&debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*) &debugCreateInfo;

    } else {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext = NULL;
    }

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
    NOTPUB_log_normal("Extentions Avaliable >>\n");
    for (int i = 0; i < extensionCount; ++i)
    {
        NOTPUB_log_normal("\t\t%s\n", Extentions[i].extensionName);
    }

    *errorCode = 0;



    return instance;
}

static VkSurfaceKHR _zse_rVK_createSurface(int *errorCode, VkInstance instance, GLFWwindow *window)
{
    VkSurfaceKHR surface;
    if (glfwCreateWindowSurface(instance, window, NULL, &surface) != VK_SUCCESS) {
        NOTPUB_log_error("failed to create window surface!");
        *errorCode = 1;
    }

    return surface;
}

static GLFWwindow* _zse_rVK_windowInit(uint32_t x, uint32_t y)
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    return glfwCreateWindow(x, y, "ZSE", NULL, NULL);
}

static int _zse_rVK_destroy
(
      GLFWwindow *window
    , VkSurfaceKHR *surface
    , VkInstance *instance
    , VkDebugUtilsMessengerEXT *debugMessenger
    , VkDevice *device
)
{
    vkDestroyDevice(*device, NULL);

    if (enableValidationLayers) {
        _zse_rVK_DestroyDebugUtilsMessengerEXT(*instance, *debugMessenger, NULL);
    }

    vkDestroySurfaceKHR(*instance, *surface, NULL);
    vkDestroyInstance(*instance, NULL);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

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
    _zse_rVK_init_deviceExtentions(&GLOBAL_rVK_deviceExtensions);

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
