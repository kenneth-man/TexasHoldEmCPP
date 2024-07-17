#pragma once

#include <stdlib.h>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include "../game/draw/draw.h"

using namespace std;

namespace Misc {
	void handleExit();
	void handleEnteringGame();
	void timer(
		int seconds,
		string description = "Timer will end"
	);
}