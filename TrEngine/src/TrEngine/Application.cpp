#include "Tepch.h"

#include "Application.h"
#include "TrEngine/Log.h"

#include "TrEngine/Event/ApplicationEvent.h"
#include "Input.h"

#include "imgui.h"
#include "TrEngine/Renderer/Renderer.h"

namespace TrEngine
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application *Application::s_Instance = nullptr;

	Application::Application()
	{
		TE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_Window->SetVSync(false);

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application() = default;

	void Application::PushLayer(Layer *layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer *layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event &e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		if (ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard)
		{
			e.SetHandled(true);
			return;
		}

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.IsHandled())
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			RenderCommand::SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());

			float time = (float)glfwGetTime();
			Timestep timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;

			for (Layer *layer : m_LayerStack)
				layer->OnUpdate(timestep);

			m_ImGuiLayer->Begin();

			for (Layer *layer : m_LayerStack)
				layer->OnImGuiRender();

			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}
	bool Application::OnWindowClose(WindowCloseEvent &e)
	{
		m_Running = false;
		return true;
	}
}