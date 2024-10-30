	#pragma once

#ifdef TE_PLATFORM_WINDOWS
	#ifdef TE_BUILD_DLL
		#define TE_API __declspec(dllexport)
	#else
		#define TRENGINE_API __declspec(dllimport)
	#endif // DEBUG
#else
	#error TrEngine support only Windows!
#endif // TE_PLATFORM_WINDOWS	

