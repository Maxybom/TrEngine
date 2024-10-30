#pragma once

#ifdef TE_PLATFORM_WINDOWS

extern TrEngine::Application* TrEngine::CreateApplication();

int main(int argc,char** argv)
{
	printf("TrEngine");
	auto app = TrEngine::CreateApplication();
	app->Run();
	delete app;
}
#endif // TE_PLATFORM_WINDOWS

