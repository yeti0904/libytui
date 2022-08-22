#ifndef LIBYTUI_TYPES_HH
#define LIBYTUI_TYPES_HH

#include "_components.hh"

namespace YTUI {
	struct Vec2 {
		size_t x, y;
	};
	struct fVec2 {
		double x, y;
	};
	struct Rect {
		size_t x, y, w, h;
	};
	struct RGBColour {
		uint8_t r, g, b;
	};
}

#endif
