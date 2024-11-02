#pragma once

#include "Core.h"  
#include "event/Event.h"
#include "TrEngine/Event/ApplicationEvent.h"
#include "Window.h"

namespace TrEngine {
	class TE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();	

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window>m_Window;
		bool m_Running = true;
	};

	//to be defined in CLIENT 
	Application* CreateApplication();
}
