#pragma once

#include <fstream>
#include <string>
#include "../file/file.h"

using namespace std;

struct Player {
	string name;
	string rank;
	int elo;
	long balance;
	int wins;
	int losses;
	int gamesPlayed;

	void init(string name);
};
