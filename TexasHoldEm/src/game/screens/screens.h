#pragma once

#include <conio.h>
#include <string>
#include <vector>
#include "../draw/draw.h"
#include "../calc/calc.h"
#include "../../player/player.h"
#include "../../inGamePlayer/inGamePlayer.h"
#include "../../constants/typeAliases.h"
#include "../../constants/variables.h"
#include "../../constants/enums.h"

// forward declaration to prevent circular dependencies
struct Player;

using namespace std;

namespace Screens {
	string infoScreen(
		string description,
		string hint
	);
	void errorScreen(string description);
	void menuScreen(
		const vector<menuItem> &menuItems,
		menuItem &selectedItem,
		Enums::GameState &gameState,
		const stateMap &stateMap,
		string hint = Variables::falsyString
	);
	void inGameScreen(
		Player &player,
		vector<InGamePlayer> &inGamePlayers,
		Enums::GameState &gameState,
		Enums::Rank gameRank
	);
}