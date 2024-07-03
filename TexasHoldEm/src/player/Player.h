#pragma once

#include <string>

using namespace std;

struct Player {
	string name;
	string rank;
	int elo;
	long balance;
	int wins;
	int losses;
	int gamesPlayed;
};
