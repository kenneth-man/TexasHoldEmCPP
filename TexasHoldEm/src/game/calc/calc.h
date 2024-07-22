#pragma once

#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <conio.h>
#include <stdint.h>
#include <stdlib.h>
#include "../../constants/typeAliases.h"
#include "../../constants/variables.h"
#include "../../constants/structs.h"
#include "../draw/draw.h"
#include "../screens/screens.h"
#include "../../inGamePlayer/inGamePlayer.h"

using namespace std;

namespace Calc {
	MenuItemsConfig initMenuItems();
	vector<InGamePlayer> initInGamePlayers(string playerName);
	vector<menuItem> menuItems(
		const vector<string> &actions,
		int colAlign,
		int rowAlign,
		int xSize = Variables::xSize,
		int ySize = Variables::ySize
	);
	bool menuAction(
		const vector<menuItem> &items,
		menuItem &selectedItem
	);
	int menuValidKeyPressed(char keyPressed);
	vector<menuItem>::iterator menuActionIt(
		const vector<menuItem> &items,
		vector<menuItem> &moveToItems,
		char keyPressed,
		int xSelected,
		int ySelected
	);
	//TODO: ELO CALCULATION/S
	//TODO: OPPONENT CHANCE OF DISCOVERING BEST HAND, BASED ON
	// PLAYER ELO (HIGHER THE ELO, HIGHER THE % AND HIGHER CHANCE OF BLUFFS)
	//TODO: TIMER TO MAKE DECISIIONS IN GAME - will have a random delay timer to
	// simulate thinking time
	//TODO: change all 'int' types to specific bits from 'stdint.h'
}