#include <libytui/libytui.hh>

int main(void) {
	YTUI::Screen screen;
	YTUI::Buffer canvas;
	YTUI::Vec2   cursorPos = {5, 5};

	YTUI::Terminal::SetCursorVisibility(false);

	canvas.Resize(screen.buf.Size());
	canvas.SetColourBG(YTUI::Colours::White);
	canvas.Clear();
	canvas.SetColourBG(YTUI::Colours::Black);

	while (true) {
		YTUI::Key key = YTUI::Input::GetKey();

		switch (key) {
			case ' ': {
				canvas.MoveCursor(cursorPos);
				canvas.PrintChar(' ');
				break;
			}
			case YTUI::Keys::Up: {
				-- cursorPos.y;
				break;
			}
			case YTUI::Keys::Down: {
				++ cursorPos.y;
				break;
			}
			case YTUI::Keys::Right: {
				++ cursorPos.x;
				break;
			}
			case YTUI::Keys::Left: {
				-- cursorPos.x;
				break;
			}
		}

		// render
		screen.buf.BlitBuffer(canvas, {0, 0});
		screen.buf.SetColourBG(YTUI::Colours::Blue);
		screen.buf.MoveCursor({cursorPos.x - 1, cursorPos.y});
		screen.buf.PrintChar('>');
		screen.buf.MoveCursor({cursorPos.x + 1, cursorPos.y});
		screen.buf.PrintChar('<');
		screen.buf.MoveCursor({cursorPos.x, cursorPos.y - 1});
		screen.buf.PrintChar('v');
		screen.buf.MoveCursor({cursorPos.x, cursorPos.y + 1});
		screen.buf.PrintChar('^');

		screen.Render();
	}
}
