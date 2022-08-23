#ifndef LIBYTUI_INPUT_HH
#define LIBYTUI_INPUT_HH

#include "_components.hh"

namespace YTUI {
	typedef uint16_t Key;

	namespace Keys {
		constexpr const Key Up     = 300;
		constexpr const Key Down   = 301;
		constexpr const Key Left   = 302;
		constexpr const Key Right  = 303;
		constexpr const Key Home   = 304;
		constexpr const Key End    = 305;
		constexpr const Key Delete = 306; 
	}
	
	namespace Input {
		char GetByte();
		Key  GetKey();
	}
}

#endif
