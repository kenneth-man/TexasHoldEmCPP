#pragma once

#include <vector>
#include <string>
#include "../../constants/typeAliases.h"

using namespace std;

namespace Calc {
	vector<menuItem> menuItems(
		vector<string> actions,
		const int xSize,
		const int ySize
	);
	string menuAction();
}