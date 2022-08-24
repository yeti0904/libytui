#include <libytui/libytui.hh>

int main(void) {
	YTUI::Screen scr;

	scr.buf.SetColourMode(YTUI::ColourMode::Colour256);

	for (size_t i = 0; i < 256; ++i) {
		scr.buf.SetColourBG(i);
		scr.buf.SetColourFG(255 - i);
		scr.buf.Print(" " + std::to_string(i) + " ");
		for (size_t j = std::to_string(i).length() + 2; j < 5; ++j) {
			scr.buf.PrintChar(' ');
		}
		if ((i + 1) % 10 == 0) {
			scr.buf.PrintChar('\n');
		}
	}

	scr.Render();

	YTUI::Input::GetByte(); // wait until key pressed
	return 0;
}
