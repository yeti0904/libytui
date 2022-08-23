#include <libytui/libytui.hh>

int main(void) {
	YTUI::Screen scr;

	while (true) {
		YTUI::Key key = YTUI::Input::GetKey(); // get user input

		switch (key) {
			case YTUI::Keys::Up: {
				scr.buf.Print("up\n");
				break;
			}
			case YTUI::Keys::Down: {
				scr.buf.Print("down\n");
				break;
			}
			case YTUI::Keys::Left: {
				scr.buf.Print("left\n");
				break;
			}
			case YTUI::Keys::Right: {
				scr.buf.Print("right\n");
				break;
			}
		}

		scr.Render();
	}
}
