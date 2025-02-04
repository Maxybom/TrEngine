#pragma once
#include "Tepch.h"
#include "imgui_impl_glfw.h"
#include "TrEngine/Layer.h"
#include "imgui.h"
#include "TrEngine/event/MouseEvent.h"
#include "TrEngine/event/KeyEvent.h"
#include "TrEngine/event/ApplicationEvent.h"
#include "TrEngine/Application.h"
#include "TrEngine/Input.h"
#include "TrEngine/KeyCode.h"

#include <unordered_map>

namespace TrEngine
{
    struct WindowData
    {
        bool isOpen = true;
        ImGuiWindowFlags flags = 0;
    };

    class TE_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent( Event& event );

        void NewWindow( const std::string& name, ImGuiWindowFlags flags = 0 );
        void CloseWindow( const std::string& name );
        void SetupDockSpace();

    private:
        bool OnMouseButtonPressedEvent( MouseButtonPressedEvent& e );
        bool OnMouseButtonReleasedEvent( MouseButtonReleasedEvent& e );
        bool OnMouseMovedEvent( MouseMovedEvent& e );
        bool OnMouseScrolledEvent( MouseScrolledEvent& e );
        bool OnKeyPressedEvent( KeyPressedEvent& e );
        bool OnKeyReleasedEvent( KeyReleasedEvent& e );
        bool OnKeyTypedEvent( KeyTypedEvent& e );
        bool OnWindowResizedEvent( WindowResizeEvent& e );

    private:
        float m_Time = 0.0f;
        std::unordered_map<std::string, WindowData> m_Windows;
    };
}