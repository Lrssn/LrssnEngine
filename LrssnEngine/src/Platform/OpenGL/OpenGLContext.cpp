#include "lepch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <GL/GL.h>

namespace LrssnEngine {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: mWindowHandle(windowHandle) 	{
		LE_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init() 	{
		glfwMakeContextCurrent(mWindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LE_CORE_ASSERT(status, "Failed to initialize Glad!");

		LE_CORE_INFO("OpenGL Info:");
		LE_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		LE_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		LE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers() 	{
		glfwSwapBuffers(mWindowHandle);
	}

}