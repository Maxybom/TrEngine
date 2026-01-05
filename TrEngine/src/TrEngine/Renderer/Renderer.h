#pragma once

#include "RenderCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"

namespace TrEngine
{

	class TE_API Renderer
	{
	public:
		static void Init();

		static void BeginScene(OrthographicCamera &camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray);

		static inline RendererAPI::API GetAPI() { return RendererAPI::getAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData *m_SceneData;
	};
}