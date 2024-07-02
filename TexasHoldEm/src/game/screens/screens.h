#pragma once

#include <conio.h>
#include <string>
#include <vector>
#include "../draw/draw.h"
#include "../calc/calc.h"
#include "../../constants/typeAliases.h"
#include "../../constants/variables.h"
#include "../../constants/enums.h"

using namespace std;

namespace Screens {
	string infoScreen(
		string description,
		string hint
	);
	void errorScreen(string description);
	void menuScreen(
		const vector<menuItem> &menuItems,
		menuItem &selectedItem,
		Enums::GameState &gameState,
		const stateMap &stateMap,
		string hint = Variables::falsyString
	);
}