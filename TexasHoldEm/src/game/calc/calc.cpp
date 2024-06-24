#include "calc.h"

vector<menuItem> Calc::menuItems(
	vector<string> actions,
	const int xSize,
	const int ySize
) {
	vector<menuItem> items;
	const int colAlign = 8;
	const int rowAlign = 4;

	const int colCount = 2;
	vector<int> colPos = {
		xSize / colCount / colCount,
		xSize / colCount + (xSize / colCount / colCount)
	};

	const int rowsModulo = actions.size() % 2;
	const int rowsDivision = actions.size() / 2;
	int rowCount = rowsModulo == 0 ? rowsDivision : rowsDivision + 1;
	const int rowOffset = ySize / rowCount;
	vector<int> rowPos;
	int currRow = 0;

	for (int i = 0; i < rowCount; ++i) {
		rowPos.push_back(rowOffset + (i * rowOffset));
	}
	
	for(size_t i = 0; i < actions.size(); ++i) {
		int x = colPos[i % 2];
		int y = rowPos[currRow];
		items.push_back(
			{
				actions[i],
				{
					x - (x / colAlign),
					y - (y / rowAlign)
				}
			}
		);
		if(i % 2 == 1) {
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

int Calc::menuValidKeyPressed(const char keyPressed) {
	switch(keyPressed) {
		case Variables::up:
		case Variables::down:
		case Variables::left:
		case Variables::right:
		case Variables::select:
			return 1;
		default:
			Draw::errorScreen("Invalid Key Pressed");
			return 0;
	}
}

vector<menuItem>::iterator Calc::menuActionIt(
	const vector<menuItem> &items,
	vector<menuItem> &moveToItems,
	const char keyPressed,
	const int xSelected,
	const int ySelected
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
	}
}