#include "screen.hh"
#include "terminal.hh"
#include "signal.hh"

YTUI::Screen::Screen() {
	YTUI::Terminal::UseAlternativeBuffer(true);
	YTUI::Terminal::SaveCursor();
	YTUI::Terminal::Clear();
	YTUI::Terminal::SetEcho(false);
	buf.Resize(YTUI::Terminal::GetSize());
	old.Resize(buf.Size());

	#ifndef LIBYTUI_PLATFORM_WINDOWS
		YTUI::SignalHandlers::Init();
	#endif
}

YTUI::Screen::~Screen() {
	YTUI::Terminal::Clear();
	YTUI::Terminal::UseAlternativeBuffer(false);
	YTUI::Terminal::RestoreCursor();
	YTUI::Terminal::SetCursorVisibility(true);
	YTUI::Terminal::ResetAttributes();
	YTUI::Terminal::SetEcho(true);
}

void YTUI::Screen::Render() {
	YTUI::Vec2 size = buf.Size();
	old.Resize(buf.Size());
	
	for (size_t i = 0; i < size.y; ++i) {
		for (size_t j = 0; j < size.x; ++j) {
			if (
				YTUI::CharacterCompare(
					buf.GetCharacter({j, i}), old.GetCharacter({j, i})
				)
			) {
				continue;
			}

			YTUI::Terminal::MoveCursor({j + 1, i + 1});
		
			auto ch = buf.GetCharacter({j, i});

			switch (ch.attr.colourMode) {
				case YTUI::ColourMode::Colour16: {
					YTUI::Terminal::SetColour(ch.attr.colour.front.byte, false);
					YTUI::Terminal::SetColour(ch.attr.colour.back.byte, true);
					break;
				}
				case YTUI::ColourMode::Colour256: {
					YTUI::Terminal::Set256Colour(ch.attr.colour.front.byte, false);
					YTUI::Terminal::Set256Colour(ch.attr.colour.back.byte, true);
					break;
				}
				case YTUI::ColourMode::Truecolour: {
					YTUI::Terminal::SetRGBColour(ch.attr.colour.front.rgb, false);
					YTUI::Terminal::SetRGBColour(ch.attr.colour.back.rgb, true);
					break;
				}
			}

			YTUI::Terminal::SetEffectAttribute(
				YTUI::EffectAttribute::Bold, ch.attr.bold
			);
			YTUI::Terminal::SetEffectAttribute(
				YTUI::EffectAttribute::Dim, ch.attr.dim
			);
			YTUI::Terminal::SetEffectAttribute(
				YTUI::EffectAttribute::Italic, ch.attr.italic
			);
			YTUI::Terminal::SetEffectAttribute(
				YTUI::EffectAttribute::Underline, ch.attr.underline
			);
			YTUI::Terminal::SetEffectAttribute(
				YTUI::EffectAttribute::Blinking, ch.attr.blinking
			);
			YTUI::Terminal::SetEffectAttribute(
				YTUI::EffectAttribute::Reverse, ch.attr.reverse
			);
			YTUI::Terminal::SetEffectAttribute(
				YTUI::EffectAttribute::Hidden, ch.attr.hidden
			);
			YTUI::Terminal::SetEffectAttribute(
				YTUI::EffectAttribute::Strikethrough, ch.attr.strikethrough
			);

			putchar(ch.ch);
		}
	}
	
	fflush(stdout);

	YTUI::Terminal::MoveCursor({buf.cursor.x + 1, buf.cursor.y + 1});

	// blit current buffer to old buffer
	old.BlitBuffer(buf, {0, 0});
}

void YTUI::Screen::UpdateBufferSize() {
	buf.Resize(YTUI::Terminal::GetSize());
}