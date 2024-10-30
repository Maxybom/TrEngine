#pragma once

#include "Core.h"  

namespace TrEngine {
	class TE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();	
	};

	//to be defined in CLIENT
	Application* CreateApplication();
}
