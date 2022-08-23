#ifndef LIBYTUI_TERMINAL_HH
#define LIBYTUI_TERMINAL_HH

#include "_components.hh"
#include "types.hh"

namespace YTUI {
	enum class EffectAttribute {
		Bold = 0,
		Dim,
		Italic,
		Underline,
		Blinking,
		Reverse,
		Hidden,
		Strikethrough
	};

	namespace Terminal {
		void       MoveCursor(const YTUI::Vec2& pos);
		void       Clear();
		YTUI::Vec2 GetSize();
		void       SetCursorVisibility(bool visible);
		void       UseAlternativeBuffer(bool use);
		void       SetColour(uint8_t colour, bool onBackground);
		void       Set256Colour(uint8_t colour, bool onBackground);
		void       SetRGBColour(const RGBColour& colour, bool onBackground);
		void       SaveCursor();
		void       RestoreCursor();
		void       SetEffectAttribute(const YTUI::EffectAttribute& effect, bool on);
		void       ResetAttributes();
		void       SetEcho(bool on);
	}
}

#endif
