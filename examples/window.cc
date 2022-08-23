#include <libytui/libytui.hh>

int main(void) {
	YTUI::Screen scr;

	YTUI::Buffer mywindow;
	mywindow.Resize({25, 5});
	mywindow.DrawBorder();
	mywindow.MoveCursor({1, 1});
	mywindow.Print("hello from this window");

	scr.buf.BlitBuffer(mywindow, {3, 3});
		// copies the contents of the window onto the main screen buffer at (3, 3)
	scr.Render();
	YTUI::Input::GetByte(); // wait until key pressed
	return 0;
}
