#include "lepch.h"
#include "WindowsWindow.h"

#include "LrssnEngine/Events/ApplicationEvent.h"
#include "LrssnEngine/Events/MouseEvent.h"
#include "LrssnEngine/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace LrssnEngine {

	static uint8_t s_GLFWWindowCount = 0;
	
	static void GLFWErrorCallback(int error, const char* description) 	{
		LE_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props) 	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) 	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow() 	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props) {
		mData.Title = props.Title;
		mData.Width = props.Width;
		mData.Height = props.Height;

		LE_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (s_GLFWWindowCount == 0) {
			LE_CORE_INFO("Initializing GLFW");
			int success = glfwInit();
			LE_CORE_ASSERT(success, "Could not intialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
		}

		mWindow = glfwCreateWindow((int)props.Width, (int)props.Height, mData.Title.c_str(), nullptr, nullptr);
		++s_GLFWWindowCount;
		mContext = CreateScope<OpenGLContext>(mWindow);
		mContext->Init();
		
		glfwSetWindowUserPointer(mWindow, &mData);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);
			});

		glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
			}
			});
		glfwSetCharCallback(mWindow, [](GLFWwindow* window, unsigned int keycode) 		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action) {
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
			}
			});

		glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
			});

		glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
			});
	}

	void WindowsWindow::Shutdown() 	{
		glfwDestroyWindow(mWindow);
		if (--s_GLFWWindowCount == 0) {
			LE_CORE_INFO("Terminating GLFW");
			glfwTerminate();
		}
	}

	void WindowsWindow::OnUpdate() 	{
		glfwPollEvents();
		mContext->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled) 	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		mData.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const 	{
		return mData.VSync;
	}

}