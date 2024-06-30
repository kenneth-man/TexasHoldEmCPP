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