#pragma once

#include <fstream>
#include <string>
#include <stdint.h>
#include "file.h"

using namespace std;

struct Player {
	string name;
	string rank;
	uint32_t elo;
	uint64_t balance;
	uint32_t wins;
	uint32_t losses;
	uint32_t gamesPlayed;

	void init(string name);
};
