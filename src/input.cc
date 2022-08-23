#include "input.hh"

char YTUI::Input::GetByte() {
	// i cant remember where i got this code from, sorry
	char ret;
	struct termios info;

	tcgetattr(0, &info);          // get current terminal attirbutes; 0 is the file descriptor for stdin
	info.c_lflag      &= ~ICANON; // disable canonical mode
	info.c_cc[VMIN]   =  1;       // wait until at least one keystroke available
	info.c_cc[VTIME]  =  0;       // no timeout
	tcsetattr(0, TCSANOW, &info); // set immediately
	
	if (read(STDIN_FILENO, &ret, 1) == -1) {
		throw std::runtime_error(strerror(errno));
	}
	
	return ret;
}

YTUI::Key YTUI::Input::GetKey() {
	char in = YTUI::Input::GetByte();
	if (in != '\x1b') {
		return in;
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
			case '3': {
				in = YTUI::Input::GetByte();
				switch (in) {
					case '~': {
						return YTUI::Keys::Delete;
					}
				}
			}
		}
	}
	return in;
}
