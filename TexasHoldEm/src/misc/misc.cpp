#include "misc.h"

void Misc::handleExit() {
	timer(3, "Program will exit");
	exit(1);
}

void Misc::handleEnteringGame() {
	timer(5, "Get Ready! Game will start");
}

void Misc::timer(
	int seconds,
	string description
) {
	while (seconds > 0) {
		Draw::title();
		Draw::text(
			description + " in " + to_string(seconds) + " seconds..."
		);

		this_thread::sleep_for(chrono::seconds(seconds / seconds));

		--seconds;
	}
}