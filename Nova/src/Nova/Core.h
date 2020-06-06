#pragma once

#ifdef NOVA_PLATFORM_WINDOWS
	#ifdef NOVA_BUILD_DLL
		#define NOVA_API __declspec(dllexport)
	#else
		#define NOVA_API __declspec(dllimport)
	#endif
#else
	#error Nova does only support Windows (for now)!
#endif