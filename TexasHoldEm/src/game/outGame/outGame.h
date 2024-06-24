#pragma once

#include "../draw/draw.h"
#include "../calc/calc.h"
#include "../../constants/variables.h"
#include "../../constants/typeAliases.h"
#include "../../constants/enums.h"

namespace OutGame {
	void auth();
	void title(
		const vector<menuItem> &menuItems,
		menuItem &selectedItem,
		Enums::OutGameState &outGameState
	);
}