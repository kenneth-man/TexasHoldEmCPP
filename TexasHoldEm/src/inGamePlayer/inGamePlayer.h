#pragma once

#include <string>
#include <stdint.h>
#include "typeAliases.h"

using namespace std;

struct InGamePlayer {
	string name;
	uint64_t betAmount; // total bet amount for a game
	uint64_t betAmountThisRound; // total bet amount for a game round
	uint64_t balance;
	cards cards;
	string action; // possible values @preflopBetActions, @standardBetActions or @miscBetActions
	bool isBot; // determine if human player or not
	bool isDeciding; // only used if not the human player
	bool isOut; // not playing; spectating
	bool isTappedOut; // has bet all their remaining money; still playing but can't take actions
	bool hasWon;
	Enums::Archetype type;
};