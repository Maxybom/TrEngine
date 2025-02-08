#pragma once
#include "Core.h"  

#include "TrEngine/LayerStack.h"

#include "TrEngine/Event/ApplicationEvent.h"

#include "Window.h"

#include "TrEngine/Renderer/Shader.h"

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

		unsigned int m_VertexArray;
		unsigned int	m_VertexBuffer;
		unsigned int	m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

		static Application* s_Instance;
	};

	//to be defined in CLIENT 
	Application* CreateApplication();
}
