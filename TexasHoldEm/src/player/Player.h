#pragma once

#include <string>
#include "../constants/enums.h"

using namespace std;

class Player {
private:
	string name;
	Enums::Rank rank;
	int elo;
	long balance;
	int wins;
	int losses;
	int gamesPlayed;
};