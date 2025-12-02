#include "Tepch.h"
#include "ImGuiLayer.h"

#include "TrEngine/Application.h"

#include <backends/imgui_impl_glfw.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace TrEngine
{
    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {}
    ImGuiLayer::~ImGuiLayer() = default;

    void ImGuiLayer::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void)io;

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

        ImGui::StyleColorsDark();
        SetDarkThemeColors();

        ImGuiStyle &style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        Application &app = Application::Get();
        GLFWwindow *window = static_cast<GLFWwindow *>(app.GetWindow().GetNativeWindow());

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");

        NewWindow("Editor", ImGuiWindowFlags_MenuBar);
        NewWindow("Console", ImGuiWindowFlags_NoCollapse);
    }

    void ImGuiLayer::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::OnEvent(Event &e)
    {
        if (m_BlockEvents)
        {
            ImGuiIO &io = ImGui::GetIO();

            if (e.IsInCategory(EventCategoryMouse) && io.WantCaptureMouse)
            {
                e.SetHandled(true);
                return;
            }

            if (e.IsInCategory(EventCategoryKeyboard) && io.WantCaptureKeyboard)
            {
                e.SetHandled(true);
                return;
            }
        }
    }

    void ImGuiLayer::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiLayer::OnImGuiRender()
    {
        SetupDockSpace();
        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        for (auto it = m_Windows.begin(); it != m_Windows.end();)
        {
            if (it->second.isOpen)
            {
                ImGui::SetNextWindowDockID(ImGui::GetID("MyDockSpace"), ImGuiCond_FirstUseEver);

                if (ImGui::Begin(it->first.c_str(), &it->second.isOpen, it->second.flags))
                {
                    ImGui::Text("Contenuto di %s", it->first.c_str());
                }
                ImGui::End();
                ++it;
            }
            else
            {
                it = m_Windows.erase(it);
            }
        }
    }

    void ImGuiLayer::End()
    {
        ImGuiIO &io = ImGui::GetIO();
        Application &app = Application::Get();
        io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow *backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void ImGuiLayer::SetupDockSpace()
    {
        ImGuiViewport *viewport = ImGui::GetMainViewport();

        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGui::SetNextWindowBgAlpha(0.0f);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::Begin("DockSpace Demo", nullptr, window_flags);

        ImGui::PopStyleVar(3);

        ImGuiIO &io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
        }

        ImGui::End();
    }

    void ImGuiLayer::NewWindow(const std::string &name, ImGuiWindowFlags flags)
    {
        m_Windows[name] = {true, flags};
    }

    void ImGuiLayer::CloseWindow(const std::string &name)
    {
        if (m_Windows.find(name) != m_Windows.end())
            m_Windows[name].isOpen = false;
    }

    void ImGuiLayer::SetDarkThemeColors()
    {
        auto &colors = ImGui::GetStyle().Colors;
        colors[ImGuiCol_WindowBg] = ImVec4{0.1f, 0.105f, 0.11f, 1.0f};
    }
}