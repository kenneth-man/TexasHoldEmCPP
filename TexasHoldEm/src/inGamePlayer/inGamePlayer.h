#pragma once

#include <string>
#include <stdint.h>
#include "typeAliases.h"

using namespace std;

struct InGamePlayer {
	string name;
	uint32_t betAmount;
	uint32_t balance;
	cards cards;
	string action; // possible values @preflopBetActions or @standardBetActions
	bool isBot; // determine if human player or not
	bool isActive; // determine if it's this current player's turn
	bool isDeciding; // only used if not the human player
	Enums::Archetype type;
};