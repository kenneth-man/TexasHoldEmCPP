#include "draw.h"

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
	for(int i = 0; i < s.length(); ++i) {
		borderStr += borderChar;
	}
	cout << borderStr << '\n';
	cout << s << '\n';
	cout << borderStr << '\n';
}

void Draw::menu(
	const vector<menuItem> &items,
	const menuItem &selectedItem,
	int xSize,
	int ySize
) {
	string output;
	int itemsRendered = 0;

	for (int col = 0; col < ySize; ++col) {
		for (int row = 0; row < xSize; ++row) {
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

				row += (int)item.length();

				itemsRendered += 1;
			}

			output += Variables::space;
		}
		output += "\n";
	}

	cout << output;
}

void Draw::list() {

}

void Draw::playingCards(
	const cards &poolCards,
	const cards &playerCards
) {
	text("* Card Pool *", true);
	cardRow(
		poolCards.first,
		poolCards.second
	);
	cout << '\n';
	text("* Your Hand *", true);
	cardRow(
		playerCards.first,
		playerCards.second
	);
}

string Draw::border(
	int col,
	int row,
	int xSize,
	int ySize
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

void Draw::cardRow(
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