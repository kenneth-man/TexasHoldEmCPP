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
		const string description,
		const string hint
	);
	void errorScreen(const string description);
	void menuScreen(
		const vector<menuItem> &menuItems,
		menuItem &selectedItem,
		Enums::GameState &gameState,
		const stateMap &stateMap
	);
}