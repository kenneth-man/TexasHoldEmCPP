#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include "draw.h"
#include "inGamePlayer.h"

using namespace std;

namespace Misc {
	void handleExit();
	void handleEnteringGame();
	void timer(
		uint8_t seconds,
		string description = "Timer will end"
	);
	void decision();
	uint64_t randomInt(
		uint64_t min,
		uint64_t diffs
	);
	////////////////////////////////////////////////////////////////////////////////
	// Template functions - Must be defined in .h file
	////////////////////////////////////////////////////////////////////////////////
	template<typename T>
	T joinVectors(
		T vec1,
		T vec2
	) {
		T newVec = {};
		newVec.insert(
			newVec.end(),
			vec1.begin(),
			vec1.end()
		);
		newVec.insert(
			newVec.end(),
			vec2.begin(),
			vec2.end()
		);
		return newVec;
	}
}