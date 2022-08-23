#include <libytui/libytui.hh>

int main(void) {
	YTUI::Screen scr;

	scr.buf.DrawLine({1, 1}, {8, 6}, '#');

	scr.Render();
	YTUI::Input::GetByte(); // wait until key pressed
	return 0;
}
