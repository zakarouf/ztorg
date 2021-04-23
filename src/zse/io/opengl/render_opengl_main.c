/*
 * ZSE Open GL front-end
 */

#include "glad/glad/glad.h"
#include <GLFW/glfw3.h>
#ifdef _WIN32
    #define APIENTRY __stdcall
#endif

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../../common.h"
#define z__Arr_getTopMT(arr)        arr.data[arr.lenUsed]
#include "../../sys/sys.h"

#define priv_LOG_MSG(format, ...)\
    z__log_basic(stdout,"\x1b[38;5;3m" "rGL:" format "\x1b[0m", ##__VA_ARGS__ )
#define priv_LOG_ERROR(format, ...)\
    z__log_basic(stdout,"\x1b[38;5;1m" "rGL:" format "\x1b[0m", ##__VA_ARGS__ )
#define priv_LOG_COLOR(color, format, ...)\
    z__log_basic(stdout, "\x1b[38;5;%dm" "rGL:" format "\x1b[0m", color, ##__VA_ARGS__ )

typedef struct {
    z__u32 VBO;
    z__u32 VAO;
    z__u32 EBO;

}_zse_rGL_object;

typedef struct {
    z__float* vertices;
    z__u32* indices;

    z__i32 verticesCount;
    z__i32 indicesCount;
}_zse_rGL__Type_vtrs;

typedef z__Arr(_zse_rGL_object) _zse_rGL_objects;
typedef z__Arr(_zse_rGL__Type_vtrs) _zse_rGL_vtrsTYPE;

typedef struct {
    GLFWwindow *_rGL_window;
    _zse_rGL_objects _rGL_buffObj;
    _zse_rGL_vtrsTYPE _rGL_vtrs;
}_zse_rGL_HANDLERS;


z__float GLOBAL_zse_rGL_vertices [] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f,

    -0.47f, -0.47f, 0.0f,
     0.5f, -0.47f, 0.0f,
     0.0f,  0.6f, 0.0f,

    -0.1f, -0.1f, 0.0f,
     0.1f, -0.1f, 0.0f,
     0.0f,  0.1f, 0.0f

};

unsigned int GLOBAL_zse_rGL_indices[] = { // note that we start from 0!
    0, 1, 2, // first triangle
    3, 4, 5,  // second triangle
    6, 7, 8  // Third triangle
};

// NOTE: TO MOVE THIS FUNCTION OR REPLACE IT
static void _zse_rGL_I_processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

static void _zse_rGL_framebuffer_size_callback(GLFWwindow* window, z__int width, z__int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow * _zse_rGL_windowInit (z__u32 x, z__u32 y)
{
    // Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    //glfwWindowHint(GLFW_DECORATED, GL_FALSE);
    //glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(x, y, "zse (Opengl)", NULL, NULL);

    if (window == NULL)
    {
        priv_LOG_ERROR("Failed to create GLFW window");
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        priv_LOG_ERROR("Failed to initialize GLAD");
        return NULL;
    }

    glViewport(0, 0, x, y);
    glfwSetFramebufferSizeCallback(window, _zse_rGL_framebuffer_size_callback);

    return window;
}

static void zse_rGL_shaderCompileStatus(z__u32 vShader)
{
    int  success;
    char infoLog[512];
    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vShader, 512, NULL, infoLog);
        priv_LOG_ERROR("ERROR:%s\n", infoLog);
    }
}

static void _zse_rGL_getShader
(
      const char * pathVert
    , const char * pathFrag
    , z__u32 *vertexShaderID
    , z__u32 *fragmentShaderID
)
{
    z__String vertShaderSource = z__String_newFromFile((char *)pathVert);
    z__String fragShaderSource = z__String_newFromFile((char *)pathFrag);
    const char *vSource = vertShaderSource.data;
    const char *fSource = fragShaderSource.data;

    *vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(*vertexShaderID , 1, &vSource, NULL);
    glCompileShader(*vertexShaderID);
    zse_rGL_shaderCompileStatus(*vertexShaderID );

    *fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(*fragmentShaderID, 1, &fSource, NULL);
    glCompileShader(*fragmentShaderID);
    zse_rGL_shaderCompileStatus(*fragmentShaderID);

    z__String_delete(&vertShaderSource);
    z__String_delete(&fragShaderSource);
}

static z__u32 _zse_rGL_createShaderProgram(const char *const pathVert, const char *const pathFrag)
{
    z__u32 vertexShaderID, fragmentShaderID;
    _zse_rGL_getShader(pathVert, pathFrag, &vertexShaderID, &fragmentShaderID);


    z__u32 shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShaderID);
    glAttachShader(shaderProgramID, fragmentShaderID);
    glLinkProgram(shaderProgramID);

    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);


    char infoLog[512] = {0};
    z__int success;
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
        priv_LOG_ERROR("ERROR:%s\n", infoLog);
    }

    return shaderProgramID;
}

static void _zse_rGL__bindObjects
(
      _zse_rGL_object* buffObj
      , z__float vertices[static 1]
      , z__u32 vertices_count
)
{
    glGenBuffers(1, &buffObj->VBO);
    glGenVertexArrays(1, &buffObj->VAO);

    glGenBuffers(1, &buffObj->EBO);

    glBindVertexArray(buffObj->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, buffObj->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(z__float) * vertices_count, vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffObj->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLOBAL_zse_rGL_indices), GLOBAL_zse_rGL_indices, GL_STATIC_DRAW);
             

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    return;
}

static void _zse_rGL_deleteShaders(z__u32 *shaders, z__u32 count)
{
    for (int i = 0; i < count; ++i)
    {
        glDeleteShader(shaders[i]);
    }
}

static void _zse_rGL_destroy(_zse_rGL_HANDLERS *handle)
{
    z__Arr_delete(&handle->_rGL_buffObj);

    glfwDestroyWindow(handle->_rGL_window);
    glfwTerminate();
    // At End
    free(handle);
}


static _zse_rGL_HANDLERS *_zse_rGL_createHandle(void)
{
    _zse_rGL_HANDLERS *handle = z__MALLOC(sizeof(_zse_rGL_HANDLERS));

    z__Arr_new(&handle->_rGL_buffObj, 8);

    handle->_rGL_window = _zse_rGL_windowInit(640, 480);

    return handle;
}


void zse_rGL_mainloop(_zse_rGL_HANDLERS *Handle)
{
    z__u32 shaderProgramID_1 = _zse_rGL_createShaderProgram("shaders/src/glT.vert", "shaders/src/glT.frag");
    z__u32 shaderProgramID_2 = _zse_rGL_createShaderProgram("shaders/src/glT.vert", "shaders/src/glT2.frag");

    _zse_rGL__bindObjects(&Handle->_rGL_buffObj.data[0], GLOBAL_zse_rGL_vertices, sizeof(GLOBAL_zse_rGL_vertices)/sizeof(z__float));


    while(!glfwWindowShouldClose(Handle->_rGL_window))
    {
        // Input
        _zse_rGL_I_processInput(Handle->_rGL_window);

        // Output/Rendering
        glClearColor(0.04f, 0.02f, 0.01f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgramID_1);
        glBindVertexArray(Handle->_rGL_buffObj.data[0].VAO);
        glDrawElements(GL_TRIANGLES, sizeof(GLOBAL_zse_rGL_indices)/sizeof(z__float), GL_UNSIGNED_INT, 0);

        // Update
        glfwSwapBuffers(Handle->_rGL_window);
        glfwPollEvents();    
    }

    glDeleteVertexArrays(1, &Handle->_rGL_buffObj.data[0].VAO);
    glDeleteBuffers(1, &Handle->_rGL_buffObj.data[0].VBO);
    glDeleteBuffers(1, &Handle->_rGL_buffObj.data[0].EBO);
    _zse_rGL_deleteShaders((z__u32[]){shaderProgramID_1, shaderProgramID_2}, 2);
}

void zse_rGL_exit(_zse_rGL_HANDLERS *rglHandle)
{
    _zse_rGL_destroy(rglHandle);
}

void zse_rGL_init(void)
{
    _zse_rGL_HANDLERS *rglHandle = _zse_rGL_createHandle();
    zse_rGL_mainloop(rglHandle);
    zse_rGL_exit(rglHandle);
}


#undef priv_LOG_MSG
#undef priv_LOG_ERROR
#undef priv_LOG_COLOR
