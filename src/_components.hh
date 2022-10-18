#ifndef LIBYTUI_COMPONENTS_HH
#define LIBYTUI_COMPONENTS_HH

#include "platform.hh"

// C standard libaries
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#ifdef LIBYTUI_PLATFORM_WINDOWS
	#include <windows.h>
#else
	#include <unistd.h>
	#include <signal.h>
	#include <termios.h>
	#include <sys/ioctl.h>
#endif

// C++ standard libraries
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <stdexcept>

#endif
