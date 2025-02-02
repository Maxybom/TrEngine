#pragma once
#include "TrEngine/Renderer/GraphicsContext.h"

class GLFWwindow;

namespace TrEngine
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext() = default;
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	
	};

	
}

