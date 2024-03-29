#include "signal.hh"
#include "_components.hh"
#include "terminal.hh"

#ifndef LIBYTUI_PLATFORM_WINDOWS

void YTUI::SignalHandlers::Init() {
	{ // Control C
		struct sigaction handler;

		handler.sa_handler = YTUI::SignalHandlers::ControlC;
		sigemptyset(&handler.sa_mask);
		handler.sa_flags = 0;

		sigaction(SIGINT, &handler, nullptr);
	}
}

void YTUI::SignalHandlers::ControlC(int) {
	YTUI::Terminal::Clear();
	YTUI::Terminal::UseAlternativeBuffer(false);
	YTUI::Terminal::RestoreCursor();
	YTUI::Terminal::SetCursorVisibility(true);
	YTUI::Terminal::ResetAttributes();
	YTUI::Terminal::SetEcho(true);
	exit(0);
}

void YTUI::SignalHandlers::Nothing(int) {
	
}

void YTUI::Signal::RunOnControlC(void (*function)(int)) {
	struct sigaction handler;

	handler.sa_handler = function;
	sigemptyset(&handler.sa_mask);
	handler.sa_flags = 0;

	sigaction(SIGINT, &handler, nullptr);
}

void YTUI::Signal::ExitOnControlC(bool exit) {
	YTUI::Signal::RunOnControlC(
		exit? YTUI::SignalHandlers::ControlC : YTUI::SignalHandlers::Nothing
	);
}

#endif
