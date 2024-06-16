#pragma once

#include <iostream>
#include <map>
#include <vector>
#include "../../constants/variables.h"
#include "../../constants/typeAliases.h"

using namespace std;

namespace Draw {
	void title();
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
	void input();
}