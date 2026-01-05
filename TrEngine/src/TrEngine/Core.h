#pragma once

#include <memory>

#ifdef TE_PLATFORM_WINDOWS
#if TE_DYNAMIC_LINK
#ifdef TE_BUILD_DLL
#define TE_API __declspec(dllexport)
#else
#define TE_API __declspec(dllimport)
#endif
#else
#define TE_API
#endif
#elif defined(TE_PLATFORM_LINUX)
#ifdef TE_BUILD_DLL
#define TE_API __attribute__((visibility("default")))
#else
#define TE_API
#endif
#else
#error TrEngine support Windows and Linux only!
#endif

#ifdef TE_ENABLE_ASSERTS
#if defined(TE_PLATFORM_WINDOWS)
#define TE_DEBUGBREAK() __debugbreak()
#elif defined(TE_PLATFORM_LINUX)
#include <signal.h>
#define TE_DEBUGBREAK() raise(SIGTRAP)
#else
#define TE_DEBUGBREAK()
#endif

#define TE_ASSERT(x, ...)                                  \
    {                                                      \
        if (!(x))                                          \
        {                                                  \
            TE_ERROR("Assertion failed:{0}", __VA_ARGS__); \
            TE_DEBUGBREAK();                               \
        }                                                  \
    }
#define TE_CORE_ASSERT(x, ...)                                   \
    {                                                            \
        if (!(x))                                                \
        {                                                        \
            TE_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); \
            TE_DEBUGBREAK();                                     \
        }                                                        \
    }
#else
#define TE_ASSERT(x, ...)
#define TE_CORE_ASSERT(x, ...)
#endif // TE_ENABLE_ASSERTS

#define BIT(x) (1 << x)

#define TE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)