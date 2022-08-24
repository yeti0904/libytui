#include <libytui/libytui.hh>

int main(void) {
	YTUI::Screen scr;

	scr.buf.options.autoScroll = true;

	while (true) {
		scr.buf.Print(std::to_string(YTUI::Input::GetByte()) + '\n');
		scr.Render();
	}
}
