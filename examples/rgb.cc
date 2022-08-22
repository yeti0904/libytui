#include <libytui/libytui.hh>

int main(void) {
	YTUI::Screen scr;

	YTUI::Terminal::SetCursorVisibility(false);

	scr.buf.SetColourMode(YTUI::ColourMode::Truecolour);
	scr.buf.SetRGBColourBG({255, 0, 0});
	scr.buf.PrintChar(' ');
	scr.buf.SetRGBColourBG({0, 255, 0});
	scr.buf.PrintChar(' ');
	scr.buf.SetRGBColourBG({0, 0, 255});
	scr.buf.PrintChar(' ');

	scr.Render();
	getchar();
	return 0;
}
