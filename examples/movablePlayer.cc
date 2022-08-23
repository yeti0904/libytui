#include <libytui/libytui.hh>

int main(void) {
	YTUI::Screen scr;
	YTUI::Vec2   playerPos = {5, 5};

	YTUI::Terminal::SetCursorVisibility(false); // disables cursor

	while (true) {
		YTUI::Key input = YTUI::Input::GetKey();

		switch (input) {
			case YTUI::Keys::Up: {
				-- playerPos.y;
				break;
			}
			case YTUI::Keys::Down: {
				++ playerPos.y;
				break;
			}
			case YTUI::Keys::Left: {
				-- playerPos.x;
				break;
			}
			case YTUI::Keys::Right: {
				++ playerPos.x;
				break;
			}
		}

		// render
		scr.buf.Clear();
		scr.buf.MoveCursor(playerPos);
		scr.buf.PrintChar('#');
		scr.Render();
	}
}
