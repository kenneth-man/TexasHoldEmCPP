#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include "draw.h"

using namespace std;

namespace Misc {
	void handleExit();
	void handleEnteringGame();
	void timer(
		uint8_t seconds,
		string description = "Timer will end"
	);
}