#include "Tepch.h"
#include "Buffer.h"
#include "Renderer.h"
#include "TrEngine/Platform/OpenGL/OpenGLBuffer.h"

namespace TrEngine
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:
			TE_CORE_ASSERT(false, "RendererAPI::None is not supported");
				return nullptr;
			case RendererAPI::OpenGL:
				return new OpenGLVertexBuffer(vertices, size);
		}
		TE_CORE_ASSERT(false, "Unknown rendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None:
			TE_CORE_ASSERT(false, "RendererAPI::None is not supported");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, size);
		}
		TE_CORE_ASSERT(false, "Unknown rendererAPI!");
		return nullptr;
	}
}