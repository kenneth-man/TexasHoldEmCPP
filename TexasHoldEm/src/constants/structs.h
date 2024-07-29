#pragma once

#include <vector>
#include "typeAliases.h"

using namespace std;

struct MenuItemsConfig {
	vector<menuItem> authScreenItems;
	vector<menuItem> titleScreenItems;
	vector<menuItem> quitScreenItems;
	vector<menuItem> newGameScreenItems;
	vector<menuItem> rankScreenItems;
};
