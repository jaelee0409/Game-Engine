#pragma once

#ifdef TR_PLATFORM_WINDOWS
#if TR_DYNAMIC_LINK
	#ifdef TR_BUILD_DLL
		#define __declspec(dllexport)
	#else
		#define __declspec(dllimport)
	#endif
#else
	#define TERRAN_API
#endif
#else
	#error Terran only supports Windows
#endif

#ifdef TR_DEBUG
	#define TR_ENABLE_ASSERTS
#endif

#ifdef TR_ENABLE_ASSERTS
	#define TR_ASSERT(x, ...) { if(!(x)) { TR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define TR_CORE_ASSERT(x, ...) { if(!(x)) { TR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define TR_ASSERT(x, ...)
	#define TR_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define TR_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)