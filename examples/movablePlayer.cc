#include <libytui/libytui.hh>

int main(void) {
	YTUI::Screen scr;
	YTUI::Vec2   playerPos = {5, 5};

	while (true) {
		YTUI::Key input = YTUI::Input::GetKey();

		switch (input) {
			case 'w': {
				-- playerPos.y;
				break;
			}
			case 's': {
				++ playerPos.y;
				break;
			}
			case 'a': {
				-- playerPos.x;
				break;
			}
			case 'd': {
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
