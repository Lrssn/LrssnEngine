#include "lepch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace LrssnEngine {

	RendererAPI* RenderCommand::s_mRendererAPI = new OpenGLRendererAPI;

}