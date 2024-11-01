#pragma once

#ifdef TE_PLATFORM_WINDOWS
#ifdef TE_BUILD_DLL
#define TE_API __declspec(dllexport)
#else
#define TE_API __declspec(dllimport)
#endif
#else
#error TrEngine support only Windows!
#endif

#define BIT(x) (1 << x)
