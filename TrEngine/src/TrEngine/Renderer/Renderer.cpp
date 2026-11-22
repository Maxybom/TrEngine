#include "Tepch.h"
#include "Renderer.h"

#include "TrEngine/Platform/OpenGL/OpenGLShader.h"
#include "TrEngine/Platform/OpenGL/OpenGLShader.h"
#include <memory>

namespace TrEngine
{
Renderer::SceneData *Renderer::m_SceneData = new Renderer::SceneData;

void Renderer::Init()
{
    RenderCommand::Init();
}

void Renderer::BeginScene(OrthographicCamera &camera)
{
    m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene()
{
}

void Renderer::Submit(const std::shared_ptr<Shader> &shader, const std::shared_ptr<VertexArray> &vertexArray, const glm::mat4 &transform)
{
    shader->Bind();
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

    //	materialInstance.Bind();

    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
}
} // namespace TrEngine
