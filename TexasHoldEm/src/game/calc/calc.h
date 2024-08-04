#pragma once

#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <conio.h>
#include <stdint.h>
#include <stdlib.h>
#include "typeAliases.h"
#include "variables.h"
#include "structs.h"
#include "enums.h"
#include "draw.h"
#include "screens.h"
#include "inGamePlayer.h"
#include "Player.h"

// forward declaration to prevent circular dependencies
struct Player;

using namespace std;

namespace Calc {
	MenuItemsConfig initMenuItems();
	vector<InGamePlayer> initInGamePlayers(string playerName);
	vector<menuItem> menuItems(
		const vector<string> &actions,
		uint32_t colAlign,
		uint32_t rowAlign,
		uint32_t xSize = Variables::xSize,
		uint32_t ySize = Variables::ySize
	);
	bool menuAction(
		const vector<menuItem> &items,
		menuItem &selectedItem
	);
	uint8_t menuValidKeyPressed(char keyPressed);
	vector<menuItem>::iterator menuActionIt(
		const vector<menuItem> &items,
		vector<menuItem> &moveToItems,
		char keyPressed,
		uint32_t xSelected,
		uint32_t ySelected
	);
	void blindBetHandle(
		Player &player,
		vector<InGamePlayer> &inGamePlayers,
		Enums::Rank gameRank,
		Enums::InGameState &inGameState
	);
	string checkInputIsValidUInt(
		string input
	);
	//TODO
	void addRandomPlayerCard(
		vector<InGamePlayer> &inGamePlayers,
		cards &uniquePlayerCards
	);
	//TODO
	void addRandomPoolCard(
		cards &poolCards,
		cards &uniquePlayerCards
	);
	//TODO: ELO CALCULATION/S
	//TODO: OPPONENT CHANCE OF DISCOVERING BEST HAND, BASED ON
	// PLAYER ELO (HIGHER THE ELO, HIGHER THE % AND HIGHER CHANCE OF BLUFFS)
	//TODO: TIMER TO MAKE DECISIIONS IN GAME - will have a random delay timer to
	// simulate thinking time
}