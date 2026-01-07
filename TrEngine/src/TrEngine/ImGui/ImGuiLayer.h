#pragma once

#include "TrEngine/Layer.h"
#include "TrEngine/Event/ApplicationEvent.h"
#include "TrEngine/Event/KeyEvent.h"
#include "TrEngine/Event/MouseEvent.h"

#include <imgui.h>
#include <unordered_map>

namespace TrEngine
{
    class TE_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;

        virtual void OnEvent(Event &e) override;

        virtual void OnUpdate(Timestep timestep) override {}

        virtual void OnImGuiRender() override;

        void Begin();
        void End();

        void SetBlockEvents(bool block) { m_BlockEvents = block; }

        void NewWindow(const std::string &name, ImGuiWindowFlags flags = 0);
        void CloseWindow(const std::string &name);

    private:
        void SetDarkThemeColors();
        void SetupDockSpace();

    private:
        bool m_BlockEvents = true;
        float m_Time = 0.0f;

        struct WindowData
        {
            bool isOpen = true;
            ImGuiWindowFlags flags = 0;
        };
        std::unordered_map<std::string, WindowData> m_Windows;
    };
}