#include "util.hh"

void YTUI::Utils::SleepMS(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
