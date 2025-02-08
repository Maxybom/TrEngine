#pragma once
#include "TrEngine/Renderer/GraphicsContext.h"

class GLFWwindow;

namespace TrEngine
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext() = default;
		~OpenGLContext();

		explicit OpenGLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}

