#pragma once

#ifdef TE_PLATFORM_WINDOWS

extern TrEngine::Application *TrEngine::CreateApplication();

int main(int argc, char **argv)
{
    TrEngine::Log::Init();
    TE_CORE_WARN("Initialized Log (Windows)!");

    int a = 5;
    TE_INFO("Hello! Var={0}", a);

    auto app = TrEngine::CreateApplication();
    app->Run();
    delete app;
}

#elif defined(TE_PLATFORM_LINUX)

extern TrEngine::Application *TrEngine::CreateApplication();

int main(int argc, char **argv)
{
    TrEngine::Log::Init();
    TE_CORE_WARN("Initialized Log (Linux)!");

    auto app = TrEngine::CreateApplication();
    app->Run();
    delete app;
    return 0; // Linux want return
}

#else
#error TrEngine support Windows and Linux only!
#endif