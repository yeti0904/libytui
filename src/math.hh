#ifndef LIBYTUI_MATH_HH
#define LIBYTUI_MATH_HH

#include "_components.hh"
#include "types.hh"

namespace YTUI {
	namespace Math {
		double      Lerp(size_t start, size_t end, double t);
		YTUI::fVec2 LerpVec(const YTUI::Vec2& start, const YTUI::Vec2& end, double t);
		size_t      DiagonalDistance(const YTUI::Vec2& start, const YTUI::Vec2& end);
	}
}

#endif
