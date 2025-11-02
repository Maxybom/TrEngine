#pragma once

#include "renderCommand.h"

namespace TrEngine
{
	/*enum class RendererAPI
	{
		None = 0,
		OpenGL = 1
	};*/

	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		static inline RendererAPI::API GetAPI() { return RendererAPI::getAPI(); }
	};
}