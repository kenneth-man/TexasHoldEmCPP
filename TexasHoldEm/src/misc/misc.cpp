#include "misc.h"

void Misc::handleExit() {
	timer(3, "Program will exit");
	exit(1);
}

void Misc::handleEnteringGame() {
	timer(5, "Get Ready! Game will start");
}

void Misc::timer(
	uint8_t seconds,
	string description
) {
	while (seconds > 0) {
		if (description != Variables::falsyString) {
			Draw::title();
			Draw::text(
				description + " in " + to_string(seconds) + " seconds..."
			);
		}

		this_thread::sleep_for(chrono::seconds(seconds / seconds));

		--seconds;
	}
}

void Misc::decision() {
	const uint8_t decisionTime = (rand() % 3) + 1;

	timer(
		decisionTime,
		Variables::falsyString
	);
}

uint64_t Misc::randomInt(
	uint64_t min,
	uint64_t diff
) {
	return rand() % diff + min;
}