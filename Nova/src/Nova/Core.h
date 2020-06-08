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

// Simple macro for shifting a '1' x amount of steps
// Used for creating bitfields (i.e. "bit masks")
// Example: BIT(2) == 100, BIT(0) == 1
#define BIT(x) (1 << x)