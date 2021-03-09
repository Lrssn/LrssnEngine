#include "lepch.h"
#include "LrssnEngine/Renderer/GraphicsContext.h"

#include "LrssnEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLContext.h"

namespace LrssnEngine {

	Scope<GraphicsContext> GraphicsContext::Create(void* window) 	{
		switch (Renderer::GetAPI()) 		{
			case RendererAPI::API::None:    LE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		LE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}