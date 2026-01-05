#include "Tepch.h"
#include "RenderCommand.h"
#include "TrEngine/Platform/OpenGL/OpenGLRendererAPI.h"

namespace TrEngine
{
	RendererAPI *RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
