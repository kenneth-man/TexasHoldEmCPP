#pragma once

#include <io.h>
#include <fcntl.h>
#include <conio.h>
#include <iostream>
#include <map>
#include <vector>
#include "../../constants/variables.h"
#include "../../constants/typeAliases.h"

using namespace std;

namespace Draw {
	void text(const string t);
	void menu(
		const vector<menuItem> &items,
		const menuItem &selectedItem,
		const int xSize,
		const int ySize
	);
	string menuBorder(
		const int col,
		const int row,
		const int xSize,
		const int ySize
	);
	void title();
	char infoScreen(
		const string description,
		const string hint
	);
	void errorScreen(const string description);
	void wideChar(
		const wchar_t *hexChar,
		bool lineBreak = false
	);
	void drawCard();
}