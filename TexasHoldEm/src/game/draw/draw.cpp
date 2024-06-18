#include "draw.h"

void Draw::text(const string s) {
	cout << s << '\n';
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

				row += (int)item.length();

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

void Draw::title() {
	system("CLS");
	text(Variables::texasHoldEm);
}

string Draw::infoScreen(
	const string description,
	const string hint
) {
	title();
	text(description);
	text("(" + hint + ")");
	string i;
	cin >> i;
	return i;
}

void Draw::errorScreen(const string description) {
	system("CLS");
	text(Variables::error);
	text(description);
	text("(Enter any key to Continue...)");
	string i;
	cin >> i;
}

// character map symbols that exceed char max size
void Draw::wideChar(
	const wchar_t *hexChar,
	bool lineBreak
) {
	// Set the mode to UTF-16
	_setmode(_fileno(stdout), _O_U16TEXT);
	
	wcout << hexChar;

	// Reset the mode back to default
	_setmode(_fileno(stdout), _O_TEXT);
	
	if (lineBreak) {
		cout << '\n';
	}
}

// TODO: draw cards with their number and symbol
	// (number in top left and bottom right, symbol/s in center OR inside border)
void Draw::drawCard() {
}