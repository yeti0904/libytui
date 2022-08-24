#include <libytui/libytui.hh>

int main(void) {
	YTUI::Screen scr;

	scr.buf.options.autoScroll = true;
	scr.buf.options.wrapText   = true;

	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;

	while (true) {
		if (r == 255) {
			if (g == 255) {
				if (b == 255) {
					YTUI::Input::GetByte();
					return 0;
				}
				++ b;
				g = 0;
			}
			else {
				++ g;
				r = 0;
			}
		}
		else {
			++ r;
		}

		scr.buf.SetColourMode(YTUI::ColourMode::Truecolour);
		scr.buf.SetRGBColourBG({r, g, b});
		scr.buf.PrintChar(' ');
		scr.Render();
	}
}
