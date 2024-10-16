#include "draw.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// static methods - these cannot be called outside this file                                            //
//////////////////////////////////////////////////////////////////////////////////////////////////////////
// output character map symbols that exceed char max size
// from `macros.h`
static void wideChar(
	const wchar_t *hexChar,
	bool lineBreak = false
) {
	// Set the mode to UTF-16
	(void)_setmode(_fileno(stdout), _O_U16TEXT);

	wcout << hexChar;

	// Reset the mode back to default
	(void)_setmode(_fileno(stdout), _O_TEXT);

	if (lineBreak) {
		cout << '\n';
	}
}

static void cardRowVals(const vector<string> &vals) {
	for (uint16_t i = 0; i < vals.size(); ++i) {
		cout << vals[i];

		if (i < vals.size() - 1) {
			cout << Variables::cardSpace;
			continue;
		}

		cout << '\n';
	}
}

static void cardRowWChars(const vector<const wchar_t *> &suitHexChars) {
	for (uint16_t i = 0; i < suitHexChars.size(); ++i) {
		cout << "|  ";
		wideChar(suitHexChars[i]);
		wideChar(suitHexChars[i]);
		wideChar(suitHexChars[i]);
		cout << "  |";

		if (i < suitHexChars.size() - 1) {
			cout << Variables::cardSpace;
			continue;
		}

		cout << '\n';
	}
}

static void cardRow(const cards &cards) {
	vector<string> firstValRows;
	vector<string> lastValRows;
	vector<string> topBottomRows;
	vector<const wchar_t *> suitHexChars;

	for (card v : cards) {
		topBottomRows.push_back("---------");

		if (v.first == "10") {
			firstValRows.push_back("| " + v.first + "    |");
			lastValRows.push_back("|    " + v.first + " |");
			suitHexChars.push_back(v.second);
			continue;
		}

		firstValRows.push_back("| " + v.first + "     |");
		lastValRows.push_back("|     " + v.first + " |");
		suitHexChars.push_back(v.second);
	}

	cardRowVals(topBottomRows);
	cardRowVals(firstValRows);
	cardRowWChars(suitHexChars);
	cardRowWChars(suitHexChars);
	cardRowWChars(suitHexChars);
	cardRowVals(lastValRows);
	cardRowVals(topBottomRows);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

void Draw::text(
	string s,
	bool border
) {
	if (!border) {
		cout << s << '\n';
		return;
	}
	const char borderChar = '*';
	string borderStr;
	for(uint16_t i = 0; i < s.length(); ++i) {
		borderStr += borderChar;
	}
	cout << borderStr << '\n';
	cout << s << '\n';
	cout << borderStr << '\n';
}

void Draw::menu(
	const vector<menuItem> &items,
	const menuItem &selectedItem,
	uint16_t xSize,
	uint16_t ySize
) {
	string output;
	uint16_t itemsRendered = 0;

	for (uint16_t col = 0; col < ySize; ++col) {
		for (uint16_t row = 0; row < xSize; ++row) {
			string b = border(col, row, xSize, ySize);

			if (b != Variables::falsyString) {
				output += b;
				continue;
			}

			if (
				itemsRendered != items.size() &&
				items[itemsRendered].second[0] == row &&
				items[itemsRendered].second[1] == col
			) {
				bool isSelected = items[itemsRendered].first == selectedItem.first;
				string item = items[itemsRendered].first;

				if (isSelected) {
					item += Variables::space;
					item += Variables::arrow;
				}

				output += item;

				row += (uint16_t)item.length();

				itemsRendered += 1;
			}

			output += Variables::space;
		}
		output += "\n";
	}

	cout << output;
}

bool Draw::inGame(
	const vector<InGamePlayer> &inGamePlayers,
	const InGamePlayer &currentInGamePlayer,
	Enums::InGameState &inGameState,
	const cards &poolCards,
	const cards &playerCards,
	menuItem &selectedMenuItem,
	const vector<menuItem> &menuItems,
	const inGameStateMap &stateMap
) {
	static Enums::InGameView inGameView = Enums::MAIN;
	bool playerActionSelected = false;

	if (currentInGamePlayer.isBot) {
		inGameView = Enums::MAIN;
	}

	const string toggleViewString(1, toupper(Variables::toggleView));
	Draw::title();

	switch(inGameView) {
		case Enums::MAIN: {
			Draw::list(
				inGamePlayers,
				currentInGamePlayer,
				inGameState
			);
			Draw::playingCards(
				poolCards,
				playerCards
			);

			if (!currentInGamePlayer.isBot) {
				const string info = "Press '" +
					toggleViewString +
					"' for the actions menu...";
				Draw::text("\n");
				Draw::text(info);

				char input = _getch();
				if (input != Variables::toggleView) {
					Screens::errorScreen("Invalid Key Pressed. " + info);
					return playerActionSelected;
				}
				inGameView = Enums::MENU;
			}
			break;
		}
		case Enums::MENU: {
			Draw::menu(
				menuItems,
				selectedMenuItem
			);
			Draw::text("\n");
			Draw::text("Press '" +
				toggleViewString +
				"' to go back to the main screen...");

			Enums::MenuAction action = Calc::menuAction(
				menuItems,
				selectedMenuItem
			);

			if (action == Enums::SELECT) {
				auto it = stateMap.find(selectedMenuItem.first);

				if (it != stateMap.end()) {
					inGameState = it->second;
					inGameView = Enums::MAIN;
					playerActionSelected = true;
					return playerActionSelected;
				}

				Screens::errorScreen("Incorrect Map of actions to enums");
			} else if (action == Enums::TOGGLEVIEW) {
				inGameView = Enums::MAIN;
			}
			break;
		}
		default: break;
	}

	return playerActionSelected;
}

void Draw::list(
	const vector<InGamePlayer> &inGamePlayers,
	const InGamePlayer &currentInGamePlayer,
	Enums::InGameState inGameState
) {
	uint64_t pot = 0;
	vector<string> playerTitles;
	uint8_t index = 1;

	for (const auto &p : inGamePlayers) {
		pot += p.betAmount ? p.betAmount : 0;
		string player = to_string(index) + ") " + p.name + "  -";
		index++;

		if (p.isDeciding) {
			player += "  DECIDING...";
		} else {
			player += "  BALANCE: \x9C" + to_string(p.balance) + "  -";
			player += "  BET: \x9C" + to_string(p.betAmount) + "  -";
			player += "  ACTION: " +
				(p.action == Variables::falsyString ?
					Variables::miscBetActions[2] :
					p.action);
		}
		if (currentInGamePlayer.name == p.name) {
			player += Variables::space;
			player += Variables::arrow;
		}

		playerTitles.push_back(player);
	}

	const string inGameStateStr = Variables::inGameStateStrMap.at(inGameState);
	const string title = "* " + inGameStateStr +
		" - POT TOTAL: \x9C" + to_string(pot) + " *";
	text(title, true);

	for (const string p : playerTitles) {
		text(p);
	}

	cout << '\n';
}

void Draw::playingCards(
	const cards &poolCards,
	const cards &playerCards
) {
	text("* Card Pool *", true);
	if (poolCards.size() > 0) {
		cardRow(poolCards);
	}

	cout << '\n';

	text("* Your Cards *", true);
	if (playerCards.size() > 0) {
		cardRow(playerCards);
	}
}

string Draw::border(
	uint16_t col,
	uint16_t row,
	uint16_t xSize,
	uint16_t ySize
) {
	const bool firstCol = col == 0;
	const bool lastCol = col == ySize - 1;
	const bool firstRow = row == 0;
	const bool lastRow = row == xSize - 1;

	if (firstRow || lastRow) {
		return Variables::xBorder;
	}
	if (firstCol || lastCol) {
		return Variables::yBorder;
	}

	return Variables::falsyString;
}

void Draw::title() {
	system("CLS");
	text(Variables::texasHoldEm);
}