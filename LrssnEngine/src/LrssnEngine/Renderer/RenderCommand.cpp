#include "lepch.h"
#include "LrssnEngine/Renderer/RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace LrssnEngine {

	Scope<RendererAPI> RenderCommand::s_mRendererAPI = RendererAPI::Create();

}