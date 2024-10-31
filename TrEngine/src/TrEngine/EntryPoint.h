#pragma once

#ifdef TE_PLATFORM_WINDOWS	

extern TrEngine::Application* TrEngine::CreateApplication();

int main(int argc, char** argv)
{
	TrEngine::Log::Init();
	TE_CORE_WARN("Inizialized log!");
	int a = 5;
	TE_INFO("Hello! Var={0}", a);

	auto app = TrEngine::CreateApplication();
	app->Run();
	delete app;
}
#endif // TE_PLATFORM_WINDOWS

