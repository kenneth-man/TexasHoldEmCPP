#pragma once

#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <conio.h>
#include "../../constants/typeAliases.h"
#include "../../constants/variables.h"
#include "../../constants/structs.h"
#include "../draw/draw.h"
#include "../screens/screens.h"

using namespace std;

namespace Calc {
	MenuItemsConfig initMenuItems();
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
}