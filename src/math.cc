#include "math.hh"

double YTUI::Math::Lerp(size_t start, size_t end, double t) {
	return (size_t) ((double) start + t * ((double) end - (double) start));
}

YTUI::fVec2 YTUI::Math::LerpVec(const YTUI::Vec2& start, const YTUI::Vec2& end, double t) {
	return {
		YTUI::Math::Lerp(start.x, end.x, t),
		YTUI::Math::Lerp(start.y, end.y, t)
	};
}

size_t YTUI::Math::DiagonalDistance(const YTUI::Vec2& start, const YTUI::Vec2& end) {
	YTUI::fVec2 distance;
	distance.x = end.x - start.x;
	distance.y = end.y - start.y;

	return std::max(abs(distance.x), abs(distance.y));
}
