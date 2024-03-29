#include "input.hh"

char YTUI::Input::GetByte() {
	#ifdef LIBYTUI_PLATFORM_WINDOWS
		return getchar();
	#else
		// i cant remember where i got this code from, sorry
		char ret;
		struct termios info;

		tcgetattr(STDIN_FILENO, &info);
			// get current terminal attirbutes; 0 is the file descriptor for stdin
		info.c_lflag      &= ~ICANON; // disable canonical mode
		info.c_cc[VMIN]   =  1;       // wait until at least one keystroke available
		info.c_cc[VTIME]  =  0;       // no timeout
		tcsetattr(0, TCSANOW, &info); // set immediately
		
		if (read(STDIN_FILENO, &ret, 1) == -1) {
			throw std::runtime_error(strerror(errno));
		}
		
		return ret;
	#endif
}

YTUI::Key YTUI::Input::GetKey() {
	char in = YTUI::Input::GetByte();

	switch (in) {
		case '\x1b': break;
		case 8:
		case 127: {
			return YTUI::Keys::Backspace;
		}
		default: {
			return in;
		}
	}

	in = YTUI::Input::GetByte();
	if (in == '[') {
		in = YTUI::Input::GetByte();

		switch (in) {
			case 'A': {
				return YTUI::Keys::Up;
			}
			case 'B': {
				return YTUI::Keys::Down;
			}
			case 'C': {
				return YTUI::Keys::Right;
			}
			case 'D': {
				return YTUI::Keys::Left;
			}
			case 'H': {
				return YTUI::Keys::Home;
			}
			case 'F': {
				return YTUI::Keys::End;
			}
			case '2': {
				in = YTUI::Input::GetByte();
				switch (in) {
					case '~': {
						return YTUI::Keys::Insert;
					}
				}
				break;
			}
			case '3': {
				in = YTUI::Input::GetByte();
				switch (in) {
					case '~': {
						return YTUI::Keys::Delete;
					}
				}
				break;
			}
			case '5': {
				in = YTUI::Input::GetByte();
				switch (in) {
					case '~': {
						return YTUI::Keys::PageUp;
					}
				}
				break;
			}
			case '6': {
				in = YTUI::Input::GetByte();
				switch (in) {
					case '~': {
						return YTUI::Keys::PageDown;
					}
				}
				break;
			}
		}
	}
	return in;
}
