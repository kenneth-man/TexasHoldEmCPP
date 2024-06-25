#pragma once

#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <conio.h>
#include "../../constants/typeAliases.h"
#include "../../constants/variables.h"
#include "../draw/draw.h"
#include "../screens/screens.h"

using namespace std;

namespace Calc {
	vector<menuItem> menuItems(
		vector<string> actions,
		const int xSize = Variables::xSize,
		const int ySize = Variables::ySize
	);
	bool menuAction(
		const vector<menuItem> &items,
		menuItem &selectedItem
	);
	int menuValidKeyPressed(const char keyPressed);
	vector<menuItem>::iterator menuActionIt(
		const vector<menuItem> &items,
		vector<menuItem> &moveToItems,
		const char keyPressed,
		const int xSelected,
		const int ySelected
	);
}