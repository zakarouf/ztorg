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
	GLFWwindow *_rGL_window;
}_zse_rGL_HANDLERS;

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
