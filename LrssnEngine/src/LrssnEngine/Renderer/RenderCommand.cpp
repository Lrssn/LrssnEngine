#include "lepch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace LrssnEngine {

	Scope<RendererAPI> RenderCommand::s_mRendererAPI = CreateScope<OpenGLRendererAPI>();

}