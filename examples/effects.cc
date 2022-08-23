#include <libytui/libytui.hh>

int main(void) {
	YTUI::Screen scr;

	scr.buf.SetEffectAttribute(YTUI::EffectAttribute::Bold, true);
	scr.buf.Print("bold\n");
	scr.buf.ResetAttributes();
	
	scr.buf.SetEffectAttribute(YTUI::EffectAttribute::Dim, true);
	scr.buf.Print("dim\n");
	scr.buf.ResetAttributes();
	
	scr.buf.SetEffectAttribute(YTUI::EffectAttribute::Italic, true);
	scr.buf.Print("italic\n");
	scr.buf.ResetAttributes();
	
	scr.buf.SetEffectAttribute(YTUI::EffectAttribute::Underline, true);
	scr.buf.Print("underline\n");
	scr.buf.ResetAttributes();
	
	scr.buf.SetEffectAttribute(YTUI::EffectAttribute::Blinking, true);
	scr.buf.Print("blinking\n");
	scr.buf.ResetAttributes();
	
	scr.buf.SetEffectAttribute(YTUI::EffectAttribute::Reverse, true);
	scr.buf.Print("reverse\n");
	scr.buf.ResetAttributes();
	
	scr.buf.SetEffectAttribute(YTUI::EffectAttribute::Hidden, true);
	scr.buf.Print("hidden\n");
	scr.buf.ResetAttributes();
	
	scr.buf.SetEffectAttribute(YTUI::EffectAttribute::Strikethrough, true);
	scr.buf.Print("strikethrough\n");
	scr.buf.ResetAttributes();

	scr.Render();
	YTUI::Input::GetByte(); // wait until key pressed
	return 0;
}
