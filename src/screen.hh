#ifndef LIBYTUI_SCREEN_HH
#define LIBYTUI_SCREEN_HH

#include "buffer.hh"

namespace YTUI {
	class Screen {
		public:
			// variables
			YTUI::Buffer old;
			YTUI::Buffer buf;

			// functions
			Screen();
			~Screen();
			void Render();
			void UpdateBufferSize();
	};
}

#endif
