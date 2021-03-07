#pragma once

#include "LrssnEngine/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace LrssnEngine {

	class OpenGLContext : public GraphicsContext 	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* mWindowHandle;
	};

}