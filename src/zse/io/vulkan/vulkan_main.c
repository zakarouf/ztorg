#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
//#include <cglm/cglm.h>

#include "../../sys/sys.h"
#include "vulkan.h"
#include <z_/imp/sys.h>
#include <z_/imp/fio.h>
#include <z_/imp/time.h>

//#define ZSE_CONFIG__rVK__LOG_DEBUG_ONLYSHOW_IMPORTANT_MESSAGES
//#define ZSE_CONFIG__rVK__MINIATURE
//#define ZSE_CONFIG__rVK__NDEBUG


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
        z__logfile_basic(stdout,"\x1b[38;5;3m" "rVK:" format "\x1b[0m", ##__VA_ARGS__ )

    #define NOTPUB_log_error(format , ...)\
        z__logfile_basic(stdout,"\x1b[38;5;1m" "rVK:ERROR:" format "\x1b[0m", ##__VA_ARGS__ )
    #define NOTPUB_log_distinct(color ,format, ...)\
        z__logfile_basic(stdout, "\x1b[38;5;%dm" "rVK:" format "\x1b[0m", color, ##__VA_ARGS__ )

#else
    #define NOTPUB_log_normal(...)\
        {;}
    #define NOTPUB_log_error(...)\
        {;}
    #define NOTNOTPUB_log_distinct(...)\
        {;}
#endif


typedef struct _zse_rvk_ts_QueueFamilyIndices {
    uint32_t graphicsFamily;
    uint32_t presentFamily;
    bool graphicsFamily_hasValue;
    bool presentFamily_hasValue;
}zse_rvk__t_QueueFamilyIndices;

typedef struct _zse_rvk_ts_SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;

    VkSurfaceFormatKHR *formats;
    uint32_t formatsSize;

    VkPresentModeKHR *presentModes;
    uint32_t presentModesSize;
}zse_rvk__t_SwapChainSupportDetails;


static int _zse_rVK_t_QueueFamilyIndices_isComplete(zse_rvk__t_QueueFamilyIndices indices)
{
    return (indices.presentFamily_hasValue & indices.graphicsFamily_hasValue);
}

typedef z__Arr(VkImage) _zse_rVK_type__swapChainImages;
typedef z__Arr(VkImageView) _zse_rVK_type__swapChainImageViews;
typedef struct _zse_rVK_ESSENTIAL_HANDLERS
{

    GLFWwindow*      _rVK_window;

    VkInstance       _rVK_vulkan_instance;

    VkPhysicalDevice _rVK_physicalDevice;
    VkDevice         _rVK_device;
    VkQueue          _rVK_graphicsQueue;
    VkQueue          _rVK_presentQueue;

    VkSurfaceKHR     _rVK_surface;

    VkSwapchainKHR   _rVK_swapChain;
    _zse_rVK_type__swapChainImages _rVK_swapChainImages;
    VkFormat _rVK_swapChainImageFormat;
    VkExtent2D _rVK_swapChainExtent;

    _zse_rVK_type__swapChainImageViews _rVK_swapChainImageViews;

    VkRenderPass _rVK_renderPass;
    VkPipelineLayout _rVK_pipelineLayout;
    VkPipeline _rVK_graphicsPipeline;

    VkDebugUtilsMessengerEXT _rVK_debugMessenger;


    z__StringList _rVK_deviceExtentions;

}_zse_rVK_HANDLERS;

static const char *GLOBAL_rVK_validationLayers = {"VK_LAYER_KHRONOS_validation"};
static const int GLOBAL_rVK_validationLayersCount = 1;

static void die(void)
{
    NOTPUB_log_distinct(36, "Dying\n");
    fflush(stdout);
    exit(-1);
}

static void _zse_rVK_init_deviceExtentions(z__StringList *dE)
{
    int device = 1;
    *dE = z__StringList_new(device);
    z__StringList_push(dE, VK_KHR_SWAPCHAIN_EXTENSION_NAME, sizeof(VK_KHR_SWAPCHAIN_EXTENSION_NAME));
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
    {                                                   \
        bool layerFound = false;                        \
        for (int i = 0; i < layerCount; i++) {          \
            if (strcmp(val, aval[i].layerName) == 0) {              \
                    layerFound = true;                              \
                    NOTPUB_log_normal(" ValidationLayer Found\n");  \
                    break;                                          \
            }                                                       \
        }                                   \
        if (!layerFound) {                  \
                free(availableLayers);      \
                return false;               \
        }                                   \
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

// DEBUGER END

static void _zse_rVK_createRenderPass(_zse_rVK_HANDLERS *Handles)
{
    // Creating Color Attachment
    VkAttachmentDescription colorAttachment = {};
    colorAttachment.format = Handles->_rVK_swapChainImageFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;

    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;

    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;


    // Creating Reference
    VkAttachmentReference colorAttachmentRef = {};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;


    // Creating Subpass
    VkSubpassDescription subpass = {};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;


    VkRenderPassCreateInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;

    if (vkCreateRenderPass(Handles->_rVK_device, &renderPassInfo, NULL, &Handles->_rVK_renderPass) != VK_SUCCESS) {
        NOTPUB_log_error("failed to create render pass!");
    }

};

static VkShaderModule _zse_rVK_createShaderModule(_zse_rVK_HANDLERS* Handle, z__Dynt code)
{
    VkShaderModuleCreateInfo createInfo = {0};

    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;

    /*
     * Shader Module only accepts codesize divisible by 4 this is
     * due to .pCode accepts code data as 4byte i.e. 32-bit unsigned
     * interger pointer. So we have to offset the size value.
     * This is probably the worst way to do so.
     * -------------------------------------------------------------
     */
    createInfo.codeSize = code.len * code.unitsize;

    createInfo.pCode = (z__u32*)code.data;

    VkShaderModule shaderModule;

    if (vkCreateShaderModule(Handle->_rVK_device, &createInfo, NULL, &shaderModule) != VK_SUCCESS) {
        NOTPUB_log_error("Failed to create shader module!\n");
    }

    return shaderModule;
}

static void _zse_rVK_createGraphicsPipeline(_zse_rVK_HANDLERS *Handle)
{
    z__Dynt vertShaderCode = z__fio_Dynt_newFromFile("shaders/v.spv", 4 ,"Vertex Shader", -1); //zse_sys_readFile("shaders/vert.spv");
    z__Dynt fragShaderCode = z__fio_Dynt_newFromFile("shaders/f.spv", 4 ,"Fragment Shader", -1); //zse_sys_readFile("shaders/frag.spv");

    if (vertShaderCode.data == NULL)
    {
        NOTPUB_log_error("Cant Load Vertex Shader: %s\n", "../shaders/vert.spv");
    }
    if (vertShaderCode.data == NULL)
    {
        NOTPUB_log_error("Cant Load Fragment Shader: %s\n", "../shaders/frag.spv");
    }

    VkShaderModule vertShaderModule = _zse_rVK_createShaderModule(Handle, vertShaderCode);
    VkShaderModule fragShaderModule = _zse_rVK_createShaderModule(Handle, fragShaderCode);



    NOTPUB_log_normal("Shader: Compilation Process:: DONE!\n");

    //die();

    VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = vertShaderModule;
    vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = fragShaderModule;
    fragShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[2] = {vertShaderStageInfo, fragShaderStageInfo};

    /* Do Stuff with Shader */

    VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = 0;
    vertexInputInfo.pVertexBindingDescriptions = NULL; // Optional
    vertexInputInfo.vertexAttributeDescriptionCount = 0;
    vertexInputInfo.pVertexAttributeDescriptions = NULL; // Optional

    VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    VkViewport viewport = {};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float) Handle->_rVK_swapChainExtent.width;
    viewport.height = (float) Handle->_rVK_swapChainExtent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor = {};
    scissor.offset.x = 0;
    scissor.offset.y = 0;
    scissor.extent = Handle->_rVK_swapChainExtent;


    VkPipelineViewportStateCreateInfo viewportState = {};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizer = {};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;

    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    /*
     *  The polygonMode determines how fragments are generated for geometry. The following modes are available:
     *    
     *    - VK_POLYGON_MODE_FILL: fill the area of the polygon with fragments
     *    - VK_POLYGON_MODE_LINE: polygon edges are drawn as lines
     *    - VK_POLYGON_MODE_POINT: polygon vertices are drawn as points
     *
    */
    rasterizer.lineWidth = 1.0f; // Thickness of a line;

    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;

    rasterizer.depthBiasEnable = VK_FALSE;
    rasterizer.depthBiasConstantFactor = 0.0f; // Optional
    rasterizer.depthBiasClamp = 0.0f; // Optional
    rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

    /* Multisampling */
    VkPipelineMultisampleStateCreateInfo multisampling = {};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    multisampling.minSampleShading = 1.0f; // Optional
    multisampling.pSampleMask = NULL; // Optional
    multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
    multisampling.alphaToOneEnable = VK_FALSE; // Optional


    VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;
    colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
    colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
    colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
    colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
    colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
    colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

    colorBlendAttachment.blendEnable = VK_TRUE;
    colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
    colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

    VkPipelineColorBlendStateCreateInfo colorBlending = {};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f; // Optional
    colorBlending.blendConstants[1] = 0.0f; // Optional
    colorBlending.blendConstants[2] = 0.0f; // Optional
    colorBlending.blendConstants[3] = 0.0f; // Optional


    
        VkDynamicState dynamicStates[] = {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_LINE_WIDTH
        };

        VkPipelineDynamicStateCreateInfo dynamicState = {};
        dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        dynamicState.dynamicStateCount = 2;
        dynamicState.pDynamicStates = dynamicStates;
    

    VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0; // Optional
    pipelineLayoutInfo.pSetLayouts = NULL; // Optional
    pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
    pipelineLayoutInfo.pPushConstantRanges = NULL; // Optional

    if (vkCreatePipelineLayout(Handle->_rVK_device, &pipelineLayoutInfo, NULL, &Handle->_rVK_pipelineLayout) != VK_SUCCESS) {
        NOTPUB_log_error("Failed to create pipeline layout!");
    }



    VkGraphicsPipelineCreateInfo pipelineInfo = {};

    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;

    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pDepthStencilState = NULL; // Optional
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = NULL; // Optional

    pipelineInfo.layout = Handle->_rVK_pipelineLayout;
    pipelineInfo.renderPass = Handle->_rVK_renderPass;
    pipelineInfo.subpass = 0;

    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE; // Optional
    pipelineInfo.basePipelineIndex = -1; // Optional



    if (vkCreateGraphicsPipelines(Handle->_rVK_device, VK_NULL_HANDLE, 1, &pipelineInfo, NULL, &Handle->_rVK_graphicsPipeline) != VK_SUCCESS) {
       NOTPUB_log_error("Failed to create graphics pipeline!\n");
    }

    // Clean up

    z__Dynt_delete(&vertShaderCode);
    z__Dynt_delete(&fragShaderCode);
    vkDestroyShaderModule(Handle->_rVK_device, fragShaderModule, NULL);
    vkDestroyShaderModule(Handle->_rVK_device, vertShaderModule, NULL);


}


/// IMAGE

static void _zse_rVK_createImageViews(_zse_rVK_HANDLERS *Handle)
{
    z__Arr_new(&Handle->_rVK_swapChainImageViews, Handle->_rVK_swapChainImages.lenUsed);

    NOTPUB_log_normal("Creating Image Views: %d\n", Handle->_rVK_swapChainImages.lenUsed);

    Handle->_rVK_swapChainImageViews.lenUsed = 0;

    for (int i = 0; i < Handle->_rVK_swapChainImages.lenUsed; i++) {
        VkImageViewCreateInfo createInfo = {};

        createInfo.flags = 0;
        createInfo.pNext = NULL;
        createInfo.subresourceRange.baseMipLevel = 0;
        createInfo.subresourceRange.levelCount = 1;
        createInfo.subresourceRange.baseArrayLayer = 0;
        createInfo.subresourceRange.layerCount = 1;
        createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;

        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        
        createInfo.image = Handle->_rVK_swapChainImages.data[i];
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;

        createInfo.format = Handle->_rVK_swapChainImageFormat;

        createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

        if (vkCreateImageView(Handle->_rVK_device, &createInfo, NULL, &Handle->_rVK_swapChainImageViews.data[i]) != VK_SUCCESS) {
            NOTPUB_log_error("failed to create image views!");
        }

        Handle->_rVK_swapChainImageViews.lenUsed += 1;
    }





}



///////

static VkExtent2D _zse_rVK__swap_chooseSwapExtent(const VkSurfaceCapabilitiesKHR* capabilities, GLFWwindow *window)
{
    if (capabilities->currentExtent.width != UINT32_MAX)
    {
        return capabilities->currentExtent;

    } else {

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        VkExtent2D actualExtent = {
            .width = width,
            .height = height
        };

        actualExtent.width  = z__MAX(capabilities->minImageExtent.width, z__MIN(capabilities->maxImageExtent.width, actualExtent.width));
        actualExtent.height = z__MAX(capabilities->minImageExtent.height, z__MIN(capabilities->maxImageExtent.height, actualExtent.height));

        return actualExtent;

    }
}

static VkPresentModeKHR _zse_rVK__swap_chooseSwapPresentMode(const VkPresentModeKHR *availablePresentModes, const uint32_t availablePresentModesCount )
{
    for (int i = 0; i < availablePresentModesCount; ++i)
    {
        if (availablePresentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
        {
            return availablePresentModes[i];
        }
    }

    return VK_PRESENT_MODE_FIFO_KHR;
}

static VkSurfaceFormatKHR _zse_rVK__swap_chooseSwapSurfaceFormat(const VkSurfaceFormatKHR *availableFormats, const uint32_t availableFormatsCount)
{
    for (int i = 0; i < availableFormatsCount; ++i)
    {
        if (    availableFormats[i].format == VK_FORMAT_B8G8R8A8_SRGB
             && availableFormats[i].colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
        {
            return availableFormats[i];
        }
    }

/*

The presentation mode is arguably the most important setting for the swap chain, 
because it represents the actual conditions for showing images to the screen.
There are four possible modes available in Vulkan:

    VK_PRESENT_MODE_IMMEDIATE_KHR:
        Images submitted by your application are transferred to the screen right away,
        which may result in tearing.

    VK_PRESENT_MODE_FIFO_KHR:
        The swap chain is a queue where the display takes an image from the front of 
        the queue when the display is refreshed and the program inserts rendered images 
        at the back of the queue. If the queue is full then the program has to wait.
        This is most similar to vertical sync as found in modern games. The moment that
        the display is refreshed is known as "vertical blank".

    VK_PRESENT_MODE_FIFO_RELAXED_KHR: 
        This mode only differs from the previous one if
    the application is late and the queue was empty at the last vertical blank. Instead
    of waiting for the next vertical blank, the image is transferred right away when it
    finally arrives. This may result in visible tearing.

    VK_PRESENT_MODE_MAILBOX_KHR: 
        This is another variation of the second mode. Instead
    of blocking the application when the queue is full, the images that are already
    queued are simply replaced with the newer ones. This mode can be used to implement
    triple buffering, which allows you to avoid tearing with significantly less latency
    issues than standard vertical sync that uses double buffering.

*/


    return availableFormats[0];
}


static zse_rvk__t_SwapChainSupportDetails _zse_rVK_t_querySwapChainSupport(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface) {
    zse_rvk__t_SwapChainSupportDetails details = {
        {0},
        0,
        0,
        0
    };

    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &details.capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, NULL);

    if (formatCount)
    {
        details.formatsSize = formatCount;
        details.formats = calloc(sizeof(VkSurfaceFormatKHR), formatCount);

        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, details.formats);
    }


    uint32_t presentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, NULL);

    if (presentModeCount) {
        details.presentModesSize = presentModeCount;
        details.presentModes = calloc(sizeof(VkSurfaceFormatKHR), presentModeCount);

        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, details.presentModes);
    }

    return details;
}

static zse_rvk__t_QueueFamilyIndices _zse_rVK__phd_findQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
static VkSwapchainKHR _zse_rVK_createSwapChain
(     VkDevice device
    , VkPhysicalDevice physicalDevice
    , VkSurfaceKHR surface
    , _zse_rVK_type__swapChainImages *swapChainImages
    , VkFormat *swapChainImageFormat
    , VkExtent2D *swapChainExtent
    , GLFWwindow *window )
{
    zse_rvk__t_SwapChainSupportDetails swapChainSupport = _zse_rVK_t_querySwapChainSupport(physicalDevice, surface);

    VkSurfaceFormatKHR surfaceFormat = _zse_rVK__swap_chooseSwapSurfaceFormat(swapChainSupport.formats, swapChainSupport.formatsSize);
    VkPresentModeKHR presentMode = _zse_rVK__swap_chooseSwapPresentMode(swapChainSupport.presentModes, swapChainSupport.presentModesSize);
    VkExtent2D extent = _zse_rVK__swap_chooseSwapExtent(&swapChainSupport.capabilities, window );

    uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;

    if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
        imageCount = swapChainSupport.capabilities.maxImageCount;
    }


    VkSwapchainCreateInfoKHR createInfo = {0};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface;

    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    zse_rvk__t_QueueFamilyIndices indices = _zse_rVK__phd_findQueueFamilies(physicalDevice, surface);

    uint32_t queueFamilyIndices[] = {indices.graphicsFamily, indices.presentFamily};

    if (indices.graphicsFamily != indices.presentFamily) {
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0; // Optional
        createInfo.pQueueFamilyIndices = NULL; // Optional
    }

    createInfo.preTransform = swapChainSupport.capabilities.currentTransform;

    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;

    createInfo.oldSwapchain = VK_NULL_HANDLE;

    VkSwapchainKHR swapChain;

    if (vkCreateSwapchainKHR(device, &createInfo, NULL, &swapChain) != VK_SUCCESS) {
        NOTPUB_log_error("Failed to create Swap Chain");
    }

    vkGetSwapchainImagesKHR(device, swapChain, &imageCount, NULL);
    z__Arr_new(swapChainImages, imageCount+1);
    vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages->data);
    swapChainImages->lenUsed = imageCount;

    *swapChainImageFormat = surfaceFormat.format;
    *swapChainExtent = extent;

    return swapChain;

}


static void _zse_rVK_cld_createLogicalDevice
(
      int *errorCode
    , VkPhysicalDevice *physicalDevice
    , VkDevice *device
    , VkQueue *graphicsQueue
    , VkQueue *presentQueue
    , VkSurfaceKHR surface
    , z__StringList *deviceExtensions
)
{
    zse_rvk__t_QueueFamilyIndices indices = _zse_rVK__phd_findQueueFamilies(*physicalDevice, surface);


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


    createInfo.enabledExtensionCount = deviceExtensions->list_len;
    createInfo.ppEnabledExtensionNames = (const char *const *)deviceExtensions->str_list;

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


static zse_rvk__t_QueueFamilyIndices _zse_rVK__phd_findQueueFamilies(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
{
    zse_rvk__t_QueueFamilyIndices indices = {0};
    
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

static bool _zse_rVK__phd_checkDeviceExtensionSupport(VkPhysicalDevice device, z__StringList *deviceExtensions) {

    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, NULL);

    VkExtensionProperties * availableExtensions = calloc(sizeof(VkExtensionProperties) ,extensionCount);
    vkEnumerateDeviceExtensionProperties(device, NULL, &extensionCount, availableExtensions);


    z__StringList requiredExtensions = z__StringList_new(deviceExtensions->list_len);
    for (int i = 0; i < GLOBAL_rVK_validationLayersCount; ++i)
    {
        z__StringList_push(&requiredExtensions, deviceExtensions->str_list[i], deviceExtensions->str_lens[i]);
    }

    //z__print(requiredExtensions, requiredExtensions.str_lens[0]);

    const uint32_t TotalExtentionsRequired = requiredExtensions.ll_used;
    uint32_t ExtentionsFound = 0;

    for (int i = 0; i < extensionCount; ++i)
    {
        for (int j = 0; j < TotalExtentionsRequired; ++j)
        {
            if (strcmp(requiredExtensions.str_list[j], availableExtensions[i].extensionName) == 0)
            {
                ExtentionsFound += 1;
            }
        }
    }


    free (availableExtensions);
    z__StringList_delete(&requiredExtensions);

    return TotalExtentionsRequired == ExtentionsFound;    
}

static int _zse_rVK__phd_isPhysicalDeviceSuitableForVulkan(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, z__StringList *deviceExtensions)
{
    zse_rvk__t_QueueFamilyIndices indices = _zse_rVK__phd_findQueueFamilies(physicalDevice, surface);

    int extensionsSupported = _zse_rVK__phd_checkDeviceExtensionSupport(physicalDevice, deviceExtensions);
    int indiceComplete = _zse_rVK_t_QueueFamilyIndices_isComplete(indices);

    bool swapChainAdequate = false;
    if (extensionsSupported) {
        zse_rvk__t_SwapChainSupportDetails swapChainSupport = _zse_rVK_t_querySwapChainSupport(physicalDevice, surface);
        swapChainAdequate = swapChainSupport.formatsSize && swapChainSupport.presentModesSize;
    }

    if (extensionsSupported  && indiceComplete && swapChainAdequate){
        NOTPUB_log_normal("Physical Device is Suitable For Vulkan\n");
        return true;
    }
    else{
        NOTPUB_log_error("Physical Device is NOT Suitable For Vulkan\n");

        if (!extensionsSupported) {
            NOTPUB_log_error("Extentions\n");
        }
        if (!indiceComplete) {
            NOTPUB_log_error("Indices Complete\n");
        }
        if (!swapChainAdequate) {
            NOTPUB_log_error("Swap Chain Adequate\n");
        }

        return false;
    }
    
}

static VkPhysicalDevice _zse_rVK_pickPhysicalDevice(int *errorCode, VkInstance instance, VkSurfaceKHR surface, z__StringList *deviceExtensions)
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

    NOTPUB_log_distinct(5, ":Using Device %d\n", deviceCount);
    
    // Fillter out devices
    for (int i = 0; i < deviceCount; ++i)
    {
        
        if (_zse_rVK__phd_isPhysicalDeviceSuitableForVulkan(devices[i], surface, deviceExtensions))
        {
            NOTPUB_log_error("AS\n");
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


static z__StringList _zse_rVK_getRequiredExtentions()
{

    z__StringList strLines = z__StringList_new(5);

    // Extentions
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    for (int i = 0; i < glfwExtensionCount; ++i)
    {
        z__StringList_push(&strLines, glfwExtensions[i], -1);
    }

    z__StringList_push(&strLines, VK_EXT_DEBUG_UTILS_EXTENSION_NAME, -1 );

    NOTPUB_log_normal("%d\n", strLines.ll_used);

    for (int i = 0; i < strLines.ll_used; ++i)
    {
        NOTPUB_log_normal(" -- EXT: %s\n", strLines.str_list[i]);        
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
    z__StringList ExtentionsLayer = _zse_rVK_getRequiredExtentions();

    createInfo.enabledExtensionCount = ExtentionsLayer.ll_used;
    createInfo.ppEnabledExtensionNames = (const char *const *) ExtentionsLayer.str_list;


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
    , VkSwapchainKHR *swapChain
    , _zse_rVK_type__swapChainImageViews *swapChainImageViews
    , VkRenderPass *renderPass
    , VkPipelineLayout *pipelineLayout
    , VkPipeline *graphicsPipeline
)
{
    vkDestroyPipeline(*device, *graphicsPipeline, NULL);
    vkDestroyPipelineLayout(*device, *pipelineLayout, NULL);
    vkDestroyRenderPass(*device, *renderPass, NULL);

    for (int i = 0; i < swapChainImageViews->lenUsed; i++) 
    {
        vkDestroyImageView(*device, swapChainImageViews->data[i], NULL);
    }
    z__Arr_delete(swapChainImageViews);

    vkDestroySwapchainKHR(*device, *swapChain, NULL);
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
    
    NOTPUB_log_distinct(6, "Initialization::Creating Vulkan Instatance\n");
    Handles->_rVK_vulkan_instance = _zse_rVK_createInstance(&errorCode);
    _zse_rVK_setupDebugMessenger(Handles->_rVK_vulkan_instance, &Handles->_rVK_debugMessenger);


    NOTPUB_log_distinct(6, "Initialization::Creating Vulkan Surface\n");
    Handles->_rVK_surface = _zse_rVK_createSurface(
          &errorCode
        , Handles->_rVK_vulkan_instance
        , Handles->_rVK_window);

    NOTPUB_log_distinct(6, "Initialization::Picking Physical Device\n");
    Handles->_rVK_physicalDevice = _zse_rVK_pickPhysicalDevice(
          &errorCode
        , Handles->_rVK_vulkan_instance
        , Handles->_rVK_surface
        , &Handles->_rVK_deviceExtentions
    );

    NOTPUB_log_distinct(6, "Initialization::Creating Logical Device\n");
    _zse_rVK_cld_createLogicalDevice(
          &errorCode
        , &Handles->_rVK_physicalDevice
        , &Handles->_rVK_device
        , &Handles->_rVK_graphicsQueue
        , &Handles->_rVK_presentQueue
        , Handles->_rVK_surface
        , &Handles->_rVK_deviceExtentions
    );

    NOTPUB_log_distinct(6, "Initialization::Creating Swap Chain\n");
    Handles->_rVK_swapChain = _zse_rVK_createSwapChain(
          Handles->_rVK_device
        , Handles->_rVK_physicalDevice
        , Handles->_rVK_surface
        , &Handles->_rVK_swapChainImages
        , &Handles->_rVK_swapChainImageFormat
        , &Handles->_rVK_swapChainExtent
        , Handles->_rVK_window

    );

    NOTPUB_log_distinct(6, "Initialization::Creating Image Views\n");
    _zse_rVK_createImageViews(Handles);

    NOTPUB_log_distinct(6, "Initialization::Creating Render Pass\n");
    _zse_rVK_createRenderPass(Handles);

    NOTPUB_log_distinct(6, "Initialization::Creating Graphics Pipe\n");
    _zse_rVK_createGraphicsPipeline(Handles);

    return errorCode;
}

static void _zse_rVK_mainLoop(GLFWwindow* window)
{
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        z__time_msleep(100);
    }
}

static _zse_rVK_HANDLERS *_zse_rVK_initHANDLES(void)
{
    _zse_rVK_HANDLERS *h = calloc(sizeof(_zse_rVK_HANDLERS), 1);
    h->_rVK_physicalDevice = VK_NULL_HANDLE;
    h->_rVK_device = 0;
    h->_rVK_vulkan_instance = 0;
    h->_rVK_debugMessenger = 0;


    _zse_rVK_init_deviceExtentions(&h->_rVK_deviceExtentions);

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
        , &HANDLES->_rVK_swapChain
        , &HANDLES->_rVK_swapChainImageViews
        , &HANDLES->_rVK_renderPass
        , &HANDLES->_rVK_pipelineLayout
        , &HANDLES->_rVK_graphicsPipeline
    );

    return 0;
}

// undefs
#undef NOTPUB_log_normal
#undef NOTPUB_log_error
#undef NOTPUB_log_distinct
