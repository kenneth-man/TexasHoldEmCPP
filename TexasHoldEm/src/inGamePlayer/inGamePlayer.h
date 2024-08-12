#pragma once

#include <string>
#include <stdint.h>
#include "typeAliases.h"

using namespace std;

struct InGamePlayer {
	string name;
	uint64_t betAmount;
	uint64_t balance;
	cards cards;
	string action; // possible values @preflopBetActions, @standardBetActions or @miscBetActions
	bool isBot; // determine if human player or not
	bool isActive; // determine if it's this current player's turn
	bool isDeciding; // only used if not the human player
	Enums::Archetype type;
};