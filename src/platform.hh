#ifndef LIBYTUI_PLATFORM_HH
#define LIBYTUI_PLATFORM_HH

#if defined(WIN32) or defined(_WIN32) or defined(__WIN32__) or defined(__NT__)
	#define LIBYTUI_PLATFORM_WINDOWS
#else
	#define LIBYTUI_PLATFORM_OTHER
#endif

#endif
