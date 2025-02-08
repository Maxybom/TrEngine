#include "Tepch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace TrEngine
{
	OpenGLContext::~OpenGLContext()= default;

	OpenGLContext::OpenGLContext( GLFWwindow* windowHandle )
		: m_WindowHandle( windowHandle )
	{
		TE_CORE_ASSERT( windowHandle, "Window handle is null" );
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent( m_WindowHandle );
		int status = gladLoadGLLoader( (GLADloadproc) glfwGetProcAddress );

		TE_CORE_ASSERT( status, "Failed to initialize Glad" );

		TE_CORE_INFO( "OpenGL INFO:" );
		TE_CORE_INFO( "Vendor: {0}",
			reinterpret_cast<const char*>(glGetString( GL_VENDOR )) );
		TE_CORE_INFO( "Renderer: {0}",
			reinterpret_cast<const char*>(glGetString( GL_RENDERER )) );
		TE_CORE_INFO( "Version: {0}",
			reinterpret_cast<const char*>(glGetString( GL_VERSION )) );
	}

	void OpenGLContext::SwapBuffers()
	{
		glBegin( GL_TRIANGLES );

		glEnd();

		glfwSwapBuffers( m_WindowHandle );
	}
}
