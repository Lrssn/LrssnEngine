#include "lepch.h"
#include "Framebuffer.h"

#include "LrssnEngine/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace LrssnEngine {

	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec) 	{
		switch (Renderer::GetAPI()) 		{
		case RendererAPI::API::None:    LE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
		}

		LE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}