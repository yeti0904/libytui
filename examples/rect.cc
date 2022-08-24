#include <libytui/libytui.hh>

int main(void) {
	YTUI::Screen scr;

	YTUI::Terminal::SetCursorVisibility(false);

	scr.buf.DrawRect({1, 1, 5, 5}, '#', false); // draw a non-filled rect
	scr.buf.DrawRect({7, 1, 5, 5}, '#', true);  // draw a filled rect

	scr.Render();

	YTUI::Input::GetByte(); // wait until key pressed
	return 0;
}
