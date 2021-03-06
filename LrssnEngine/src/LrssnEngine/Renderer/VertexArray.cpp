#include "lepch.h"
#include "LrssnEngine/Renderer/VertexArray.h"

#include "LrssnEngine/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace LrssnEngine {

	Ref<VertexArray> VertexArray::Create() 	{
		switch (Renderer::GetAPI()) 		{
			case RendererAPI::API::None:    LE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
		}

		LE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}