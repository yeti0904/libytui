#include "terminal.hh"

void YTUI::Terminal::MoveCursor(const YTUI::Vec2& pos) {
	printf("\x1b[%i;%if", (int) pos.y, (int) pos.x);
}

void YTUI::Terminal::Clear() {
	fputs("\x1b[2J", stdout);
	YTUI::Terminal::MoveCursor({1, 1});
}

YTUI::Vec2 YTUI::Terminal::GetSize() {
	struct winsize size;
	if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == -1) {
		throw std::runtime_error(strerror(errno));
	}

	return {size.ws_col, size.ws_row};
}

void YTUI::Terminal::SetCursorVisibility(bool visible) {
	fputs("\x1b[?25", stdout);
	putchar(visible? 'h' : 'l');
}

void YTUI::Terminal::UseAlternativeBuffer(bool use) {
	fputs("\x1b[?1049", stdout);
	putchar(use? 'h' : 'l');
}

void YTUI::Terminal::SetColour(uint8_t colour, bool onBackground) {
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
		}
		case YTUI::EffectAttribute::Italic: {
			printf("\x1b[%im", on? 3 : 23);
		}
		case YTUI::EffectAttribute::Underline: {
			printf("\x1b[%im", on? 4 : 24);
		}
		case YTUI::EffectAttribute::Blinking: {
			printf("\x1b[%im", on? 5 : 25);
		}
		case YTUI::EffectAttribute::Reverse: {
			printf("\x1b[%im", on? 7 : 27);
		}
		case YTUI::EffectAttribute::Hidden: {
			printf("\x1b[%im", on? 8 : 28);
		}
		case YTUI::EffectAttribute::Strikethrough: {
			printf("\x1b[%im", on? 9 : 29);
		}
	}
}

void YTUI::Terminal::ResetAttributes() {
	fputs("\x1b[0m", stdout);
}
