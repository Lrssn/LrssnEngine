#include "lepch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace LrssnEngine {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: mWindowHandle(windowHandle) 	{
		LE_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init() 	{
		LE_PROFILE_FUNCTION();
		glfwMakeContextCurrent(mWindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		LE_CORE_ASSERT(status, "Failed to initialize Glad!");

		LE_CORE_INFO("OpenGL Info:");
		LE_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		LE_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		LE_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
		LE_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "LrssnEngine requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers() 	{
		LE_PROFILE_FUNCTION();
		glfwSwapBuffers(mWindowHandle);
	}

}