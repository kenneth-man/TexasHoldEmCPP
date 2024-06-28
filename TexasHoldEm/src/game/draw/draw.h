#pragma once

#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include "../../constants/variables.h"
#include "../../constants/typeAliases.h"

using namespace std;

namespace Draw {
	void text(const string t);
	// TODO: not spaced correctly if 2 options e.g. for Auth screen
	void menu(
		const vector<menuItem> &items,
		const menuItem &selectedItem,
		const int xSize = Variables::xSize,
		const int ySize = Variables::ySize
	);
	string menuBorder(
		const int col,
		const int row,
		const int xSize,
		const int ySize
	);
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