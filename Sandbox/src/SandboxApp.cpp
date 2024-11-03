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
        TE_INFO("ExampleLayer::Update");
    }

    void OnEvent(TrEngine::Event& event) override
    {
        TE_TRACE("{0}", event);
    }
};

class Sandbox : public TrEngine::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }
    ~Sandbox()
    {

    }
};

TrEngine::Application* TrEngine::CreateApplication()
{
    return new Sandbox();
}
