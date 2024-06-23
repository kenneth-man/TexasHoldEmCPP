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

char Draw::infoScreen(
	const string description,
	const string hint
) {
	title();
	text(description);
	text("(" + hint + ")");
	return _getch();
}

void Draw::errorScreen(const string description) {
	system("CLS");
	text(Variables::error);
	text(description);
	text("(Enter any key to Continue...)");
	// typecast to void, to suppress warning 'Return Value Ignored...'
	(void)_getch();
}

// output character map symbols that exceed char max size
// from `macros.h`
void Draw::wideChar(
	const wchar_t *hexChar,
	bool lineBreak
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

void Draw::cards(
	const vector<string> &vals,
	const vector<const wchar_t *> &suitHexChars
) {
	vector<string> firstValRows;
	vector<string> lastValRows;
	vector<string> topBottomRows;

	for (string v : vals) {
		topBottomRows.push_back("---------");

		if (v == "10") {
			firstValRows.push_back("| " + v + "    |");
			lastValRows.push_back("|    " + v + " |");
			continue;
		}
		
		firstValRows.push_back("| " + v + "     |");
		lastValRows.push_back("|     " + v + " |");
	}

	cardRowVals(topBottomRows);
	cardRowVals(firstValRows);
	cardRowWChars(suitHexChars);
	cardRowWChars(suitHexChars);
	cardRowWChars(suitHexChars);
	cardRowVals(lastValRows);
	cardRowVals(topBottomRows);
}

void Draw::cardRowVals(
	const vector<string> &vals
) {
	for (int i = 0; i < vals.size(); ++i) {
		cout << vals[i];

		if (i < vals.size() - 1) {
			cout << Variables::cardSpace;
			continue;
		}

		cout << '\n';
	}
}

void Draw::cardRowWChars(
	const vector<const wchar_t *> &suitHexChars
) {
	for(int i = 0; i < suitHexChars.size(); ++i) {
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