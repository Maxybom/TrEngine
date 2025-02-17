#include <TrEngine.h>

class ExampleLayer : public TrEngine::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    void OnUpdate() override
    {
        if (TrEngine::Input::IsKeyPressed( TE_KEY_TAB ))
        {
        }
    }

    void OnEvent(TrEngine::Event& event) override
    {
        if (event.GetEventType() == TrEngine::EventType::KeyPressed)
        {
            TrEngine::KeyPressedEvent&e = (TrEngine::KeyPressedEvent&)event;
            TE_TRACE("{0}",e.GetKeyCode());
        }
    }
};

class Sandbox : public TrEngine::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
        PushOverlay(new TrEngine::ImGuiLayer());
    }
    ~Sandbox()
    {

    }
};

TrEngine::Application* TrEngine::CreateApplication()
{
    return new Sandbox();
}
