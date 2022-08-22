#ifndef LIBYTUI_INPUT_HH
#define LIBYTUI_INPUT_HH

#include "_components.hh"

namespace YTUI {
	typedef uint16_t Key;

	namespace Keys {
		constexpr const Key Up    = 300;
		constexpr const Key Down  = 301;
		constexpr const Key Left  = 302;
		constexpr const Key Right = 303;
	}
	
	namespace Input {
		char GetByte();
		Key  GetKey();
	}
}

#endif
