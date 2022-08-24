#include "buffer.hh"
#include "math.hh"

bool YTUI::CharacterCompare(const Character& ch1, const Character& ch2) {
	if (ch1.ch != ch2.ch) {
		return false;
	}
	if (ch1.attr.colourMode != ch2.attr.colourMode) {
		return false;
	}
	switch (ch1.attr.colourMode) {
		case YTUI::ColourMode::Colour256:
		case YTUI::ColourMode::Colour16: {
			if (
				(ch1.attr.colour.back.byte != ch2.attr.colour.back.byte) ||
				(ch1.attr.colour.front.byte != ch2.attr.colour.front.byte)
			) {
				return false;
			}
			break;
		}
		case YTUI::ColourMode::Truecolour: {
			if (
				(ch1.attr.colour.back.rgb != ch2.attr.colour.back.rgb) ||
				(ch1.attr.colour.front.rgb != ch2.attr.colour.front.rgb)
			) {
				return false;
			}
		}
	}

	return (
		(ch1.attr.bold == ch2.attr.bold) &&
		(ch1.attr.dim == ch2.attr.dim) &&
		(ch1.attr.italic == ch2.attr.italic) &&
		(ch1.attr.underline == ch2.attr.underline) &&
		(ch1.attr.blinking == ch2.attr.blinking) &&
		(ch1.attr.reverse == ch2.attr.reverse) &&
		(ch1.attr.hidden == ch2.attr.hidden) &&
		(ch1.attr.strikethrough == ch2.attr.strikethrough)
	);
}

YTUI::Buffer::Buffer() {
	cursor           = {0, 0};
	options.wrapText = false;
}

void YTUI::Buffer::Resize(const YTUI::Vec2& size) {
	buf.resize(size.y);
	for (auto& line : buf) {
		line.resize(size.x);
	}
}

YTUI::Vec2 YTUI::Buffer::Size() {
	if (buf.size() == 0) {
		return {0, 0};
	}
	return {buf[0].size(), buf.size()};
}

YTUI::Character& YTUI::Buffer::GetCharacter(const YTUI::Vec2& pos) {
	return buf.at(pos.y).at(pos.x);
}

void YTUI::Buffer::Print(const std::string& text) {
	for (auto& ch : text) {
		PrintChar(ch);
	}
}

void YTUI::Buffer::PrintChar(const char ch) {
	switch (ch) {
		case '\r': {
			cursor.x = 0;
			break;
		}
		case '\n': {
			++ cursor.y;
			cursor.x = 0;

			if (options.autoScroll && (cursor.y >= buf.size())) {
				ScrollDown(1);
			}
			
			break;
		}
		default: {
			if ((cursor.x < Size().x) && (cursor.y < Size().y)) {
				buf.at(cursor.y).at(cursor.x) = YTUI::Character(ch, attr);
			}
			++ cursor.x;
			if (options.wrapText && (cursor.x >= Size().x)) {
				++ cursor.y;
				cursor.x = 0;
			}
		}
	}
}

void YTUI::Buffer::ResetAttribute() {
	attr = YTUI::Attribute();
}

void YTUI::Buffer::SetColourFG(Colour colour) {
	if (
		(attr.colourMode != YTUI::ColourMode::Colour16) &&
		(attr.colourMode != YTUI::ColourMode::Colour256)
	) {
		throw std::runtime_error("SetColourFG cannot be used with current colour mode");
	}
	attr.colour.front.byte = colour;
}

void YTUI::Buffer::SetColourBG(Colour colour) {
	if (
		(attr.colourMode != YTUI::ColourMode::Colour16) &&
		(attr.colourMode != YTUI::ColourMode::Colour256)
	) {
		throw std::runtime_error("SetColourBG cannot be used with current colour mode");
	}
	attr.colour.back.byte = colour;
}

void YTUI::Buffer::SetRGBColourFG(RGBColour colour) {
	if (attr.colourMode != YTUI::ColourMode::Truecolour) {
		throw std::runtime_error("SetRGBColourFG cannot be used with current colour mode");
	}
	attr.colour.front.rgb = colour;
}

void YTUI::Buffer::SetRGBColourBG(RGBColour colour) {
	if (attr.colourMode != YTUI::ColourMode::Truecolour) {
		throw std::runtime_error("SetRGBColourBG cannot be used with current colour mode");
	}
	attr.colour.back.rgb = colour;
}

void YTUI::Buffer::SetColourMode(const ColourMode& mode) {
	attr.colourMode = mode;
}

void YTUI::Buffer::Clear() {
	for (auto& line : buf) {
		for (auto& ch : line) {
			ch.ch   = ' ';
			ch.attr = attr;
		}
	}
}

void YTUI::Buffer::MoveCursor(const YTUI::Vec2& pos) {
	cursor = pos;
}

void YTUI::Buffer::DrawBorder() {
	if (buf.empty()) {
		return;
	}
	if (buf[0].empty()) {
		return;
	}
	YTUI::Vec2 size = Size();
	
	GetCharacter({0, 0}).ch                   = '+';
	GetCharacter({size.x - 1, 0}).ch          = '+';
	GetCharacter({0, size.y - 1}).ch          = '+';
	GetCharacter({size.x - 1, size.y - 1}).ch = '+';
	for (size_t i = 1; i < size.x - 1; ++i) {
		GetCharacter({i, 0}).ch          = '-';
		GetCharacter({i, size.y - 1}).ch = '-';
	}
	for (size_t i = 1; i < size.y - 1; ++i) {
		GetCharacter({0, i}).ch          = '|';
		GetCharacter({size.x - 1, i}).ch = '|';
	}
}

void YTUI::Buffer::BlitBuffer(Buffer& buffer, const YTUI::Vec2& position) {
	YTUI::Vec2 size   = buffer.Size();
	YTUI::Vec2 mysize = Size();

	for (size_t i = 0; i < size.y; ++i) {
		for (size_t j = 0; j < size.x; ++j) {
			if ((position.x + j < mysize.x) && (position.y + i < mysize.y)) {
				buf[position.y + i][position.x + j] = buffer.GetCharacter({j, i});
			}
		}
	}
}

void YTUI::Buffer::DrawRect(const YTUI::Rect& rect, char material, bool fill) {
	YTUI::Vec2 size = Size();

	if (!fill) {
		DrawLine({rect.x, rect.y}, {rect.x + rect.w - 1, rect.y}, material);
		DrawLine({rect.x, rect.y}, {rect.x, rect.y + rect.h}, material);
		DrawLine(
			{rect.x + rect.w - 1, rect.y}, {rect.x + rect.w, rect.y + rect.h}, material
		);
		DrawLine(
			{rect.x, rect.y + rect.h - 1}, {rect.x + rect.w, rect.y + rect.h - 1},
			material
		);
		return;
	}

	for (size_t i = rect.y; i < rect.y + rect.h; ++i) {
		for (size_t j = rect.x; j < rect.x + rect.w; ++j) {
			if ((i < size.y) && (j < size.x)) {
				buf[i][j] = YTUI::Character(material, attr);
			}
		}
	}
}

void YTUI::Buffer::DrawLine(
	const YTUI::Vec2& start, const YTUI::Vec2& end, char material
) {
	// https://www.redblobgames.com/grids/line-drawing.html

	size_t     length = YTUI::Math::DiagonalDistance(start, end);
	YTUI::Vec2 size   = Size();

	for (size_t i = 0; i < length; ++i) {
		double t = i == 0? 0.0 : (double) i / (double) length;
		YTUI::fVec2 interpolated = YTUI::Math::LerpVec(start, end, t);
		YTUI::Vec2 point = {
			(size_t) round(interpolated.x),
			(size_t) round(interpolated.y)
		};

		if ((point.x < size.x) && (point.y < size.y)) {
			GetCharacter(point) = Character(material, attr);
		}
	}
}

void YTUI::Buffer::ResetAttributes() {
	attr = YTUI::Attribute();
}

void YTUI::Buffer::SetEffectAttribute(const YTUI::EffectAttribute& effect, bool on) {
	switch (effect) {
		case YTUI::EffectAttribute::Bold: {
			attr.bold = on;
			break;
		}
		case YTUI::EffectAttribute::Dim: {
			attr.dim = on;
			break;
		}
		case YTUI::EffectAttribute::Italic: {
			attr.italic = on;
			break;
		}
		case YTUI::EffectAttribute::Underline: {
			attr.underline = on;
			break;
		}
		case YTUI::EffectAttribute::Blinking: {
			attr.blinking = on;
			break;
		}
		case YTUI::EffectAttribute::Reverse: {
			attr.reverse = on;
			break;
		}
		case YTUI::EffectAttribute::Hidden: {
			attr.hidden = on;
			break;
		}
		case YTUI::EffectAttribute::Strikethrough: {
			attr.strikethrough = on;
			break;
		}
	}
}

void YTUI::Buffer::ScrollDown(size_t lines) {
	for (size_t i = 0; i < lines; ++i) {
		buf.erase(buf.begin());

		std::vector <YTUI::Character> newLine;
		for (size_t j = 0; j < Size().x; ++j) {
			newLine.push_back(YTUI::Character(' ', attr));
		}

		buf.push_back(newLine);
	}

	cursor.y -= lines;
}
