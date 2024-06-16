#include "draw.h"

void Draw::title() {

}

void Draw::menu(
	const vector<menuItem> &items,
	const menuItem &selectedItem,
	const int xSize,
	const int ySize
) {
	string output;
	int itemsRendered = 0;

	for (int col = 0; col < ySize; ++col) {
		for (int row = 0; row < xSize; ++row) {
			string border = menuBorder(col, row, xSize, ySize);

			if (border != Variables::falsyString) {
				output += border;
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

				row += item.length();

				itemsRendered += 1;
			}

			output += Variables::space;
		}
		output += "\n";
	}

	cout << output;
}

string Draw::menuBorder(
	const int col,
	const int row,
	const int xSize,
	const int ySize
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

void Draw::input() {

}