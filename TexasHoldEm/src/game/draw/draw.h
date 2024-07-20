#pragma once

#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include "../../constants/variables.h"
#include "../../constants/typeAliases.h"

using namespace std;

namespace Draw {
	void text(
		string t,
		bool border = false
	);
	void menu(
		const vector<menuItem> &items,
		const menuItem &selectedItem,
		int xSize = Variables::xSize,
		int ySize = Variables::ySize
	);
	//TODO: `list` function to display
	//  - current 'phase' of the game (flop, flop bet, river ....)
	//	- title of list section centered
	//	- display players
	//	- bet amounts
	//	- actions
	// and a marker for current player's turn - will have a random delay timer to
	// simulate thinking time
	void list();
	void playingCards(
		const cards &poolCards,
		const cards &playerCards
	);
	string border(
		int col,
		int row,
		int xSize,
		int ySize
	);
	void title();
	void wideChar(
		const wchar_t *hexChar,
		bool lineBreak = false
	);
	void cardRow(
		const vector<string> &vals,
		const vector<const wchar_t *> &suitHexChars // possible values @suitHexChars
	);
	void cardRowVals(const vector<string> &vals);
	void cardRowWChars(
		const vector<const wchar_t *> &suitHexChars  // possible values @suitHexChars
	);
}