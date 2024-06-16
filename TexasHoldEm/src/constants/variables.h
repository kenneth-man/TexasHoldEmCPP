#pragma once

#include <map>
#include <vector>
#include <string>
#include "./typeAliases.h"

using namespace std;

namespace Variables {
	const char up = 'w';
	const char left = 'a';
	const char down = 's';
	const char right = 'd';
	const char select = 'p';
	const char space = ' ';
	const string falsyString = "";
	const string xBorder = "|";
	const string yBorder = "-";
	// TODO: Option on title screen to set height and width of terminal
		// to recalc xSizeGameMenu and ySizeGameMenu and inGameMenu
	const int xSizeGameMenu = 120;
	const int ySizeGameMenu = 20;
	const string arrow = "<--";
	// TODO: make values dynamic x and y values based on xSizeGameMenu and ySizeGameMenu
	const vector<menuItem> inGameMenu = {
		{ "FOLD", {5, 5} },
		{ "CALL", {5, 10} },
		{ "RAISE", {5, 15} }
	};
}