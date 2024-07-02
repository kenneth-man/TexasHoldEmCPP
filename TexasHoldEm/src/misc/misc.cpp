#include "misc.h"

void Misc::handleExit() {
	int seconds = 3;
	
	while (seconds > 0) {
		Draw::title();
		Draw::text(
			"Program will exit in " + to_string(seconds) + " seconds..."
		);

		this_thread::sleep_for(chrono::seconds(seconds/seconds));
		
		--seconds;
	}

	exit(1);
}