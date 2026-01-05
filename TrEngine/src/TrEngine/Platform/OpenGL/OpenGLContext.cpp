#include "Tepch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace TrEngine
{
    OpenGLContext::~OpenGLContext() = default;

    OpenGLContext::OpenGLContext(GLFWwindow *windowHandle)
        : m_WindowHandle(windowHandle)
    {
        TE_CORE_ASSERT(windowHandle, "Window handle is null");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        TE_CORE_ASSERT(status, "Failed to initialize Glad");

        TE_CORE_INFO("OpenGL INFO:");
        TE_CORE_INFO("  Vendor: {0}", (const char *)glGetString(GL_VENDOR));
        TE_CORE_INFO("  Renderer: {0}", (const char *)glGetString(GL_RENDERER));
        TE_CORE_INFO("  Version: {0}", (const char *)glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}