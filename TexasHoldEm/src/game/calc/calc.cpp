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

// TODO: update `selectedItem` base don key pressed (move arrow for menu items)
string Calc::menuAction() {
	return ""; // satisfy compiler for now
}