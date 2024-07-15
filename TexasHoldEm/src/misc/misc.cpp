#include "misc.h"

void Misc::handleExit() {
	timer(3);
	exit(1);
}

void Misc::timer(int seconds) {
	while (seconds > 0) {
		Draw::title();
		Draw::text(
			"Program will exit in " + to_string(seconds) + " seconds..."
		);

		this_thread::sleep_for(chrono::seconds(seconds / seconds));

		--seconds;
	}
}