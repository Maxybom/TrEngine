#include "Tepch.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "TrEngine/Platform/OpenGL/OpenGLVertexArray.h"

namespace TrEngine
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:		TE_CORE_ASSERT(false, "RendererAPI::None is not supported");
		case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		}

		TE_CORE_ASSERT(false, "Unknown rendererAPI!");
		return nullptr;
	}
}