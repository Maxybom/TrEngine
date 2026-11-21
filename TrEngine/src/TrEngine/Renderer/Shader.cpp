#include "Tepch.h"
#include "Renderer.h"
#include "TrEngine/Platform/OpenGL/OpenGLShader.h"
#include "VertexArray.h"

namespace TrEngine {

Shader *Shader::Create(const std::string &vertexSource,
                       const std::string &fragmentSource) {
  switch (Renderer::GetAPI()) {
  case RendererAPI::API::None:
    TE_CORE_ASSERT(false, "RendererAPI::None is not supported");
  case RendererAPI::API::OpenGL:
    return new OpenGLShader(vertexSource, fragmentSource);
  }

  TE_CORE_ASSERT(false, "Unknown rendererAPI!");
  return nullptr;
}

} // namespace TrEngine
