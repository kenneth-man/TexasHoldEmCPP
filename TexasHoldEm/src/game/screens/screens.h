#pragma once

#include <conio.h>
#include <string>
#include <vector>
#include "draw.h"
#include "calc.h"
#include "player.h"
#include "inGamePlayer.h"
#include "typeAliases.h"
#include "variables.h"
#include "enums.h"

// forward declaration to prevent circular dependencies
struct Player;

using namespace std;

namespace Screens {
	string infoScreen(
		string description,
		string hint,
		bool quit = false
	);
	void errorScreen(string description);
	void menuScreen(
		const vector<menuItem> &menuItems,
		menuItem &selectedItem,
		Enums::GameState &gameState,
		const gameStateMap &stateMap,
		string hint = Variables::falsyString
	);
	void inGameScreen(
		Player &player,
		vector<InGamePlayer> &inGamePlayers,
		Enums::GameState &gameState,
		Enums::Rank gameRank
	);
}