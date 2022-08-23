#include <libytui/libytui.hh>

int main(void) {
	YTUI::Screen scr;

	YTUI::Terminal::SetCursorVisibility(false);

	scr.buf.SetColourMode(YTUI::ColourMode::Truecolour); // enables RGB truecolour
	scr.buf.SetRGBColourBG({255, 0, 0}); // red
	scr.buf.PrintChar(' ');
	scr.buf.SetRGBColourBG({0, 255, 0}); // green
	scr.buf.PrintChar(' ');
	scr.buf.SetRGBColourBG({0, 0, 255}); // blue
	scr.buf.PrintChar(' ');

	scr.Render();
	YTUI::Input::GetByte(); // wait until key pressed
	return 0;
}
