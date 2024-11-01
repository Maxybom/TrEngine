#pragma once
#include <memory>
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace TrEngine {
    class TE_API Log {
    public:
        static void Init();
        static std::shared_ptr<spdlog::logger>& GetCoreLogger();
        static std::shared_ptr<spdlog::logger>& GetClientLogger();
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// Core log macros
#define TE_CORE_ERROR(...) ::TrEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TE_CORE_WARN(...)  ::TrEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TE_CORE_INFO(...)  ::TrEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TE_CORE_TRACE(...) ::TrEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TE_CORE_FATAL(...) ::TrEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define TE_ERROR(...)       ::TrEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define TE_WARN(...)        ::TrEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TE_INFO(...)        ::TrEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define TE_TRACE(...)       ::TrEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TE_FATAL(...)       ::TrEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)
