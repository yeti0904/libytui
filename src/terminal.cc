#include "terminal.hh"

void YTUI::Terminal::MoveCursor(const YTUI::Vec2& pos) {
	#ifdef LIBYTUI_PLATFORM_WINDOWS
		COORD winpos = {(short) pos.x, (short) pos.y};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), winpos);
	#else
		printf("\x1b[%i;%if", (int) pos.y, (int) pos.x);
	#endif
}

void YTUI::Terminal::Clear() {
	#ifdef LIBYTUI_PLATFORM_WINDOWS
		HANDLE                     handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO screen;
		DWORD                      written;

		GetConsoleScreenBufferInfo(handle, &screen);
		FillConsoleOutputCharacterA(
			handle, ' ', screen.dwSize.X * screen.dwSize.Y, {0, 0}, &written
		);
	    FillConsoleOutputAttribute(
	        handle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
	        screen.dwSize.X * screen.dwSize.Y, {0, 0}, &written
	    );
	#else
		fputs("\x1b[2J", stdout);
		YTUI::Terminal::MoveCursor({1, 1});
	#endif
}

YTUI::Vec2 YTUI::Terminal::GetSize() {
	#ifdef LIBYTUI_PLATFORM_WINDOWS
		CONSOLE_SCREEN_BUFFER_INFO screen;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screen);

		return {
			(size_t) (screen.srWindow.Right - screen.srWindow.Left + 1),
			(size_t) (screen.srWindow.Bottom - screen.srWindow.Top + 1)
		};
	#else
		struct winsize size;
		if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == -1) {
			throw std::runtime_error(strerror(errno));
		}
	
		return {size.ws_col, size.ws_row};
	#endif
}

void YTUI::Terminal::SetCursorVisibility(bool visible) {
	#ifdef LIBYTUI_PLATFORM_WINDOWS
		HANDLE              handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO cursor;
		GetConsoleCursorInfo(handle, &cursor);

		cursor.bVisible = visible? TRUE : FALSE;

		SetConsoleCursorInfo(handle, &cursor);
	#else
		fputs("\x1b[?25", stdout);
		putchar(visible? 'h' : 'l');
	#endif
}

void YTUI::Terminal::UseAlternativeBuffer(bool use) {
	#ifdef LIBYTUI_PLATFORM_WINDOWS
		return;
	#endif
	fputs("\x1b[?1049", stdout);
	putchar(use? 'h' : 'l');
}

void YTUI::Terminal::SetColour(uint8_t colour, bool onBackground) {
	#ifdef LIBYTUI_PLATFORM_WINDOWS
		return;
	#endif
	printf("\x1b[%im", colour + (onBackground? 10 : 0));
}

void YTUI::Terminal::Set256Colour(uint8_t colour, bool onBackground) {
	printf("\x1b[%i;5;%im", 38 + (onBackground? 10 : 0), colour);
}

void YTUI::Terminal::SetRGBColour(const RGBColour& colour, bool onBackground) {
	printf(
		"\x1b[%i;2;%i;%i;%im", 38 + (onBackground? 10 : 0),
		colour.r, colour.g, colour.b
	);
}

void YTUI::Terminal::SaveCursor() {
	fputs("\x1b 7", stdout);
}

void YTUI::Terminal::RestoreCursor() {
	fputs("\x1b 8", stdout);
}

void YTUI::Terminal::SetEffectAttribute(const YTUI::EffectAttribute& effect, bool on) {
	switch (effect) {
		case YTUI::EffectAttribute::Bold: {
			printf("\x1b[%im", on? 1 : 22);
			break;
		}
		case YTUI::EffectAttribute::Dim: {
			printf("\x1b[%im", on? 2 : 22);
			break;
		}
		case YTUI::EffectAttribute::Italic: {
			printf("\x1b[%im", on? 3 : 23);
			break;
		}
		case YTUI::EffectAttribute::Underline: {
			printf("\x1b[%im", on? 4 : 24);
			break;
		}
		case YTUI::EffectAttribute::Blinking: {
			printf("\x1b[%im", on? 5 : 25);
			break;
		}
		case YTUI::EffectAttribute::Reverse: {
			printf("\x1b[%im", on? 7 : 27);
			break;
		}
		case YTUI::EffectAttribute::Hidden: {
			printf("\x1b[%im", on? 8 : 28);
			break;
		}
		case YTUI::EffectAttribute::Strikethrough: {
			printf("\x1b[%im", on? 9 : 29);
			break;
		}
	}
}

void YTUI::Terminal::ResetAttributes() {
	fputs("\x1b[0m", stdout);
}

void YTUI::Terminal::SetEcho(bool on) {
	#ifdef LIBYTUI_PLATFORM_WINDOWS
		HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
		DWORD  mode   = 0;
		GetConsoleMode(handle, &mode);

		if (on) {
			mode |= ENABLE_ECHO_INPUT;
		}
		else {
			mode &= ~ENABLE_ECHO_INPUT;
		}

		SetConsoleMode(handle, mode);
	#else
		struct termios term;
		tcgetattr(STDIN_FILENO, &term);
	
		if (on) {
			term.c_lflag |= ECHO;
		}
		else {
			term.c_lflag &= ~ECHO;
		}
		tcsetattr(STDIN_FILENO, 0, &term);
	#endif
}
