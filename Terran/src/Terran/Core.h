#pragma once

#ifdef TR_PLATFORM_WINDOWS
	#ifdef TR_BUILD_DLL
		#define TERRAN_API __declspec(dllexport)
	#else
		#define TERRAN_API __declspec(dllimport)
	#endif
#else
	#error Terran only supports Windows
#endif

#define BIT(x) (1 << x)