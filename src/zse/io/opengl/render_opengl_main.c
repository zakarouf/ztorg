/*
 * ZSE Open GL front-end
 */

#include "glad/glad/glad.h"
#include <GLFW/glfw3.h>
#ifdef _WIN32
    #define APIENTRY __stdcall
#endif

#include <stdlib.h>
#include <stdio.h>

#include "../../common.h"
#include "../../sys/sys.h"

#define priv_LOG_MSG(format, ...)\
	zse_sys_log(stdout,"\x1b[38;5;3m" "rGL:" format "\x1b[0m", ##__VA_ARGS__ )
#define priv_LOG_ERROR(format, ...)\
	zse_sys_log(stdout,"\x1b[38;5;1m" "rGL:" format "\x1b[0m", ##__VA_ARGS__ )
#define priv_LOG_COLOR(color, format, ...)\
	zse_sys_log(stdout, "\x1b[38;5;%dm" "rGL:" format "\x1b[0m", color, ##__VA_ARGS__ )

typedef struct {
	z__u32 VBO;
	z__u32 VAO;
	z__u32 EBO;

}_zse_rGL_objects;

typedef struct {
	GLFWwindow *_rGL_window;
	_zse_rGL_objects _rGL_buffObj;
}_zse_rGL_HANDLERS;


z__float GLOBAL_zse_rGL_vertices [9] = {
	  -0.5f, -0.5, 0.0f
	,  0.5f, -0.5, 0.0f
	,  0.0f,  0.5, 0.0f
};


// NOTE: TO MOVE THIS FUNCTION OR REPLACE IT
static void _zse_rGL_I_processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
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

static z__u32 _zse_rGL_getShader
(
	  const char * pathVert
	, const char * pathFrag
	, z__u32 *vertexShaderID
	, z__u32 *fragmentShaderID
)
{
	z__String vertShaderSource = z__String_createFromFile((char *)pathVert);
	z__String fragShaderSource = z__String_createFromFile((char *)pathFrag);

	*vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(*vertexShaderID , 1, (const char * const *)&vertShaderSource.data, NULL);
    glCompileShader(*vertexShaderID);
    zse_rGL_shaderCompileStatus(*vertexShaderID );

    *fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(*fragmentShaderID, 1, (const char * const *)&fragShaderSource.data, NULL);
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

    return shaderProgramID;

}

static void _zse_rGL_destroy(_zse_rGL_HANDLERS *handle)
{
	
	glfwDestroyWindow(handle->_rGL_window);
	glfwTerminate();
	// At End
	free(handle);
}

static _zse_rGL_HANDLERS *_zse_rGL_createHandle(void)
{
	_zse_rGL_HANDLERS *handle = z__MALLOC(sizeof(_zse_rGL_HANDLERS));

	handle->_rGL_window = _zse_rGL_windowInit(640, 480);

	return handle;
}

static z__int _zse_rGL__drawTriangle
(
	  _zse_rGL_objects* buffObj
	  , z__float vertices[static 9]
	  , z__u32 vertices_count
)
{
	glGenBuffers(1, &buffObj->VBO);


	glBindBuffer(GL_ARRAY_BUFFER, buffObj->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(z__float) * vertices_count, vertices, GL_STATIC_DRAW);

	return 1;
}


void zse_rGL_mainloop(_zse_rGL_HANDLERS *Handle)
{
	while(!glfwWindowShouldClose(Handle->_rGL_window))
	{
		// Input
		_zse_rGL_I_processInput(Handle->_rGL_window);

		// Output/Rendering
		glClearColor(0.9f, 0.5f, 0.7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Update
	    glfwSwapBuffers(Handle->_rGL_window);
	    glfwPollEvents();    
	}
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
