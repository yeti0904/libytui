#include <libytui/libytui.hh>

int main(void) {
	YTUI::Screen scr;

	scr.buf.SetColourMode(YTUI::ColourMode::Colour256); // attributes now may use 256 colours
	scr.buf.SetColourFG(255);
	scr.buf.SetColourBG(239);
	scr.buf.Print("Hello world");

	scr.Render();
	getchar();
	return 0;
}
