#pragma once
#include "imgui.h"

#include "Event.h"
#include "TrEngine/event/MouseEvent.h"
#include "TrEngine/event/KeyEvent.h"
#include "TrEngine/event/ApplicationEvent.h"
#include "TrEngine/KeyCode.h"

namespace TrEngine
{
    class ImGuiEventHandler
    {
    public:
        void HandleEvent(Event& event);

    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(MouseMovedEvent& e);
        bool OnMouseScrolledEvent(MouseScrolledEvent& e);
        bool OnKeyPressedEvent(KeyPressedEvent& e);
        bool OnKeyReleasedEvent(KeyReleasedEvent& e);
        bool OnKeyTypedEvent(KeyTypedEvent& e);
        bool OnWindowResizedEvent(WindowResizeEvent& e);
    };
}
