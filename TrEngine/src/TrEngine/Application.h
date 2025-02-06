#pragma once
#include "Core.h"  
#include "TrEngine/LayerStack.h"

#include "TrEngine/event/Event.h"
#include "TrEngine/Event/ApplicationEvent.h"

#include "Window.h"

#include "TrEngine/Renderer/Shader.h"

//#include "TrEngine/ImGui/ImGuiLayer.h"

namespace TrEngine
{
	class TE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* laye);

		inline static Application& Get() { return*s_Instance; }

		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window>m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
		//ImGuiLayer* m_ImGuiLayer;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
	private:
		static Application* s_Instance;
	};

	//to be defined in CLIENT 
	Application* CreateApplication();
}
