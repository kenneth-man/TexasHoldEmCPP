#pragma once

#include <string>
#include <stdint.h>
#include "typeAliases.h"

using namespace std;

struct InGamePlayer {
	string name;
	uint32_t betAmount;
	cards cards;
	string action; // possible values @actions
	bool isBot;
};