#include "calc.h"

MenuItemsConfig Calc::initMenuItems() {
	MenuItemsConfig config;

	config.authScreenItems = menuItems(
		Variables::authScreenActions,
		Variables::authMenuColAlign,
		Variables::authMenuRowAlign
	);
	config.titleScreenItems = menuItems(
		Variables::titleScreenActions,
		Variables::titleMenuColAlign,
		Variables::titleMenuRowAlign
	);
	config.quitScreenItems = menuItems(
		Variables::yesNoScreenActions,
		Variables::quitMenuColAlign,
		Variables::quitMenuRowAlign
	);
	config.newGameScreenItems = menuItems(
		Variables::yesNoScreenActions,
		Variables::newGameMenuColAlign,
		Variables::newGameMenuRowAlign
	);
	config.rankScreenItems = menuItems(
		Variables::rankScreenActions,
		Variables::rankMenuColAlign,
		Variables::rankMenuRowAlign
	);

	return config;
}

vector<InGamePlayer> Calc::initInGamePlayers(string playerName) {
	vector<InGamePlayer> output;
	vector<string> names = Variables::opponentNames;
	uint8_t maxPlayers = 6;

	while (output.size() < maxPlayers) {
		size_t index = rand() % names.size();

		output.push_back({
			names[index],
			0,
			{},
			Variables::falsyString,
			true
		});

		names.erase(names.begin() + index);
	}

	size_t playerIndex = rand() % output.size();
	output.at(playerIndex) = {
		playerName,
		0,
		{},
		Variables::falsyString,
		false
	};

	return output;
}

vector<menuItem> Calc::menuItems(
	const vector<string> &actions,
	int colAlign,
	int rowAlign,
	int xSize,
	int ySize
) {
	vector<menuItem> items;

	const int colCount = 2;
	vector<int> colPositions = {
		xSize / colCount / colCount,
		xSize / colCount + (xSize / colCount / colCount)
	};

	const int modulo = (int)actions.size() % 2;
	const int half = (int)actions.size() / 2;
	int rowCount = modulo == 0 ? half : half + 1;
	const int rowOffset = ySize / rowCount;
	vector<int> rowPositions;
	int currRow = 0;

	for (int i = 0; i < rowCount; ++i) {
		rowPositions.push_back(rowOffset + (i * rowOffset));
	}
	
	for (size_t i = 0; i < actions.size(); ++i) {
		int x = colPositions[i % 2];
		int y = rowPositions[currRow];
		items.push_back(
			{
				actions[i],
				{
					x - (x / colAlign),
					y - (y / rowAlign)
				}
			}
		);
		if (i % 2 == 1) {
			++currRow;
		}
	}

	return items;
}

bool Calc::menuAction(
	const vector<menuItem> &items,
	menuItem &selectedItem
) {
	const int x = selectedItem.second[0];
	const int y = selectedItem.second[1];
	vector<menuItem> moveToItems;

	char input = _getch();
	char keyPressed = tolower(input);

	if (!menuValidKeyPressed(keyPressed)) {
		return false;
	}

	vector<menuItem>::iterator it = menuActionIt(
		items,
		moveToItems,
		keyPressed,
		x,
		y
	);

	switch (keyPressed) {
		case Variables::up:
		case Variables::left: {
			if (it == moveToItems.begin()) {
				selectedItem = *(--moveToItems.end());
			} else {
				selectedItem = *(--it);
			}
			break;
		}
		case Variables::down:
		case Variables::right: {
			if (it == --moveToItems.end()) {
				selectedItem = *(moveToItems.begin());
			} else {
				selectedItem = *(++it);
			}
			break;
		}
		case Variables::select:
			return true;
	}

	return false;
}

int Calc::menuValidKeyPressed(char keyPressed) {
	switch(keyPressed) {
		case Variables::up:
		case Variables::down:
		case Variables::left:
		case Variables::right:
		case Variables::select:
			return 1;
		default:
			Screens::errorScreen("Invalid Key Pressed");
			return 0;
	}
}

vector<menuItem>::iterator Calc::menuActionIt(
	const vector<menuItem> &items,
	vector<menuItem> &moveToItems,
	char keyPressed,
	int xSelected,
	int ySelected
) {
	switch (keyPressed) {
		case Variables::up:
		case Variables::down: {
			for (const menuItem &m : items) {
				if (m.second[0] == xSelected) moveToItems.push_back(m);
			}
			return find_if(
				moveToItems.begin(),
				moveToItems.end(),
				[ySelected](menuItem el) { return el.second[1] == ySelected; }
			);
		}
		case Variables::left:
		case Variables::right: {
			for (const menuItem &m : items) {
				if (m.second[1] == ySelected) moveToItems.push_back(m);
			}
			return find_if(
				moveToItems.begin(),
				moveToItems.end(),
				[xSelected](menuItem el) { return el.second[0] == xSelected; }
			);
		}
		default:
			return moveToItems.end();
	}
}