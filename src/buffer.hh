#ifndef LIBYTUI_BUFFER_HH
#define LIBYTUI_BUFFER_HH

#include "_components.hh"
#include "types.hh"
#include "colours.hh"
#include "types.hh"
#include "terminal.hh"

namespace YTUI {
	typedef uint8_t Colour;

	union ColourUnion {
		Colour    byte;
		RGBColour rgb;
	};

	struct ColourPair {
		ColourUnion front;
		ColourUnion back;
	};

	enum class ColourMode {
		Colour16 = 0,
		Colour256,
		Truecolour
	};

	struct Attribute {
		ColourPair colour;
		ColourMode colourMode;
		bool       bold;
		bool       dim;
		bool       italic;
		bool       underline;
		bool       blinking;
		bool       reverse;
		bool       hidden;
		bool       strikethrough;

		Attribute():
			colourMode(ColourMode::Colour16),
			bold(false),
			dim(false),
			italic(false),
			underline(false),
			blinking(false),
			reverse(false),
			hidden(false),
			strikethrough(false)
		{
			colour.front.byte = YTUI::Colours::Default;
			colour.back.byte  = YTUI::Colours::Default;
			colour.front.rgb  = {0, 0, 0};
			colour.back.rgb  = {0, 0, 0};
		}
	};

	struct Character {
		char      ch;
		Attribute attr;

		Character():
			ch(' ')
		{}
		Character(char p_ch):
			ch(p_ch)
		{}
		Character(char p_ch, Attribute p_attr):
			ch(p_ch),
			attr(p_attr)
		{}
	};

	bool CharacterCompare(const Character& ch1, const Character& ch2);

	struct BufferOptions {
		bool wrapText;
		bool autoScroll;
	};

	class Buffer {
		private:
			std::vector <std::vector <Character>> buf;
		public:
			// variables
			YTUI::Vec2    cursor;
			BufferOptions options;
			Attribute     attr;
			
			Buffer();
			Buffer(std::vector <std::vector <char>> from);
			void             Resize(const YTUI::Vec2& size);
			YTUI::Vec2       Size();
			YTUI::Character& GetCharacter(const YTUI::Vec2& pos);
			void             Print(const std::string& text);
			void             PrintChar(const char ch);
			void             ResetAttribute();
			void             SetColourFG(Colour colour);
			void             SetColourBG(Colour colour);
			void             SetRGBColourFG(RGBColour colour);
			void             SetRGBColourBG(RGBColour colour);
			void             SetColourMode(const ColourMode& mode);
			void             Clear();
			void             MoveCursor(const YTUI::Vec2& pos);
			void             DrawBorder();
			void             BlitBuffer(Buffer& buffer, const YTUI::Vec2& position);
			void             DrawRect(const YTUI::Rect& rect, char material, bool fill);
			void             DrawLine(
				const YTUI::Vec2& start, const YTUI::Vec2& end, char material
			);
			void             ResetAttributes();
			void             SetEffectAttribute(const EffectAttribute& effect, bool on);
			void             ScrollDown(size_t lines);
	};
}

#endif
