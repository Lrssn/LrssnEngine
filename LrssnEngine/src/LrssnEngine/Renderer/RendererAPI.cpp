#include "lepch.h"
#include "LrssnEngine/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace LrssnEngine {

	RendererAPI::API RendererAPI::s_mAPI = RendererAPI::API::OpenGL;
	
	Scope<RendererAPI> RendererAPI::Create() 	{
		switch (s_mAPI) 		{
			case RendererAPI::API::None:    LE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateScope<OpenGLRendererAPI>();
		}

		LE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}