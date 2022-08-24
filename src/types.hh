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

		bool operator==(RGBColour value) const {
			return (
				(r == value.r) &&
				(g == value.g) &&
				(b == value.b)
			);
		}
		bool operator!=(RGBColour value) const {
			return (
				(r != value.r) ||
				(g != value.g) ||
				(b != value.b)
			);
		}
	};
}

#endif
