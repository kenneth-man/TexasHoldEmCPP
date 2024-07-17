#pragma once

#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include "../../constants/variables.h"
#include "../../constants/typeAliases.h"

using namespace std;

namespace Draw {
	void text(string t);
	void menu(
		const vector<menuItem> &items,
		const menuItem &selectedItem,
		int xSize = Variables::xSize,
		int ySize = Variables::ySize
	);
	string menuBorder(
		int col,
		int row,
		int xSize,
		int ySize
	);
	//TODO: refactor `menuBorder` to it can be used with `List` and `Sprite` functions
	//TODO: `List` function to display (left 50% of terminal):
	//	- title of list section centered
	//	- display players
	//	- bet amounts
	//	- actions
	// and a marker for current player's turn - will have a random delay timer to
	// simulate thinking time
	//TODO: `Sprite` function to display row of cards used for (right 50% of terminal):
	//	- card pool
	//	- player hand underneath
	void title();
	void wideChar(
		const wchar_t *hexChar,
		bool lineBreak = false
	);
	void cards(
		const vector<string> &vals,
		const vector<const wchar_t *> &suitHexChars
	);
	void cardRowVals(const vector<string> &vals);
	void cardRowWChars(const vector<const wchar_t *> &suitHexChars);
}