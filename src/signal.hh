#ifndef LIBYTUI_SIGNAL_HH
#define LIBYTUI_SIGNAL_HH

#ifndef LIBYTUI_PLATFORM_WINDOWS

namespace YTUI {
	namespace SignalHandlers {
		void Init();
		void ControlC(int);
		void Nothing(int);
	}
	namespace Signal {
		void RunOnControlC(void (*function)(int));
		void ExitOnControlC(bool exit);
	}
}

#endif

#endif
