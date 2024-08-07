#include "calc.h"

MenuItemsConfig Calc::initMenuItems() {
	MenuItemsConfig config;

	config.authScreenItems = menuItems(
		Variables::authScreenActions,
		Variables::standardMenuColAlign,
		Variables::standardMenuRowAlign
	);
	config.titleScreenItems = menuItems(
		Variables::titleScreenActions,
		Variables::standardMenuColAlign,
		Variables::titleMenuRowAlign
	);
	config.quitScreenItems = menuItems(
		Variables::yesNoScreenActions,
		Variables::standardMenuColAlign,
		Variables::standardMenuRowAlign
	);
	config.newGameScreenItems = menuItems(
		Variables::yesNoScreenActions,
		Variables::standardMenuColAlign,
		Variables::standardMenuRowAlign
	);
	config.rankScreenItems = menuItems(
		Variables::rankScreenActions,
		Variables::standardMenuColAlign,
		Variables::rankMenuRowAlign
	);

	return config;
}

InGameMenuItemsConfig Calc::initInGameMenuItems() {
	InGameMenuItemsConfig config;

	config.preflopBetItems = menuItems(
		Variables::preflopBetActions,
		Variables::standardMenuColAlign,
		Variables::standardMenuRowAlign
	);
	config.standardBetItems = menuItems(
		Variables::standardBetActions,
		Variables::standardMenuColAlign,
		Variables::standardMenuRowAlign
	);

	return config;
}

vector<InGamePlayer> Calc::initInGamePlayers(string playerName) {
	vector<InGamePlayer> output;
	vector<string> names = Variables::opponentNames;

	while (output.size() < Variables::maxPlayers) {
		size_t index = rand() % names.size();

		output.push_back({
			names[index],
			0,
			{},
			Variables::falsyString,
			true,
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
		false,
		true
	};

	return output;
}

vector<menuItem> Calc::menuItems(
	const vector<string> &actions,
	uint32_t colAlign,
	uint32_t rowAlign,
	uint32_t xSize,
	uint32_t ySize
) {
	vector<menuItem> items;

	const uint8_t colCount = 2;
	vector<uint32_t> colPositions = {
		xSize / colCount / colCount,
		xSize / colCount + (xSize / colCount / colCount)
	};

	const uint32_t modulo = (uint32_t)actions.size() % 2;
	const uint32_t half = (uint32_t)actions.size() / 2;
	uint8_t rowCount = modulo == 0 ? half : half + 1;
	const uint32_t rowOffset = ySize / rowCount;
	vector<uint32_t> rowPositions;
	uint32_t currRow = 0;

	for (auto i = 0; i < rowCount; ++i) {
		rowPositions.push_back(rowOffset + (i * rowOffset));
	}
	
	for (auto i = 0; i < actions.size(); ++i) {
		uint32_t x = colPositions[i % 2];
		uint32_t y = rowPositions[currRow];
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
	const uint32_t x = selectedItem.second[0];
	const uint32_t y = selectedItem.second[1];
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

uint8_t Calc::menuValidKeyPressed(char keyPressed) {
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
	uint32_t xSelected,
	uint32_t ySelected
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

void Calc::blindBetHandle(
	Player &player,
	vector<InGamePlayer> &inGamePlayers,
	Enums::Rank gameRank,
	Enums::InGameState &inGameState
) {
	const rankBetRange range = Variables::ranksBetRangeMap
		.at(gameRank);

	if (player.name != inGamePlayers[inGameState].name) {
		uint32_t bet = rand() % range.second.second;
		if (inGameState == Enums::SMALLBLINDBET) {
			inGamePlayers[inGameState].betAmount = bet == 0 ?
				range.second.first :
				bet;
			inGameState = Enums::BIGBLINDBET;
		} else {
			const uint32_t diff = range.second.second - inGamePlayers[0].betAmount;
			while(bet < inGamePlayers[0].betAmount) {
				bet = diff == 0 ?
					range.second.second :
					rand() % diff + inGamePlayers[0].betAmount;
			}
			inGamePlayers[inGameState].betAmount = bet;
			inGameState = Enums::DEALING;
		}
		return;
	}

	const string betName = inGameState == Enums::SMALLBLINDBET ?
		"Small Blind" :
		"Big Blind";
	const string description = "Please enter your " + betName + " bet";
	const string hint = "Bets for " + range.first + " games must be between " +
		to_string(range.second.first) + " and " + to_string(range.second.second);
	string input;

	while(1) {
		input = Screens::infoScreen(
			description,
			hint,
			true
		);

		if (input == Variables::quit) {
			inGameState = Enums::EARLYEND;
			return;
		}

		const string error = checkInputIsValidUInt(input);

		if (error != Variables::falsyString) {
			Screens::errorScreen(error);
			continue;
		}

		const uint32_t bet = stoi(input);

		if (player.balance < bet) {
			const string hint = "You don't have enough funds to make this bet. Your current balance is \x9C" +
				to_string(player.balance);
			Screens::errorScreen(hint);
			continue;
		}

		if (inGameState == Enums::SMALLBLINDBET) {
			if (bet < range.second.first || bet > range.second.second) {
				Screens::errorScreen(hint);
				continue;
			}
			inGamePlayers[inGameState].betAmount = bet;
			inGameState = Enums::BIGBLINDBET;
			return;
		} else {
			if (bet < inGamePlayers[0].betAmount) {
				const string hint = "Big Blind Bets must be >= the Small Blind Bet which was \x9C" +
					to_string(inGamePlayers[0].betAmount);
				Screens::errorScreen(hint);
				continue;
			}
			if (bet > range.second.second) {
				Screens::errorScreen(hint);
				continue;
			}
			inGamePlayers[inGameState].betAmount = bet;
			inGameState = Enums::DEALING;
			return;
		}
	}
}

void Calc::preflopBetHandle(
	Player &player,
	vector<InGamePlayer> &inGamePlayers,
	Enums::Rank gameRank,
	Enums::InGameState &inGameState
) {
	
}

void Calc::standardBetHandle(
	Player &player,
	vector<InGamePlayer> &inGamePlayers,
	Enums::Rank gameRank,
	Enums::InGameState &inGameState
) {

}

string Calc::checkInputIsValidUInt(
	string input
) {
	try {
		const int32_t i = stoi(input);

		if (i < 0) {
			return "Key must be an unsigned integer; it cannot be negative";
		}

		return Variables::falsyString;
	}
	catch (const invalid_argument &_) {
		// suppress 'unreferenced local variable' compile warning
		(void)_;
		return "Key must be an unsigned integer; it cannot contain letters or symbols";
	}
	catch (const out_of_range &_) {
		(void)_;
		return "Key exceeds the max number of a 4 byte integer";
	}
}

void Calc::addRandomPlayerCard(
	vector<InGamePlayer> &inGamePlayers,
	cards &uniqueCards
) {
	for (uint8_t i = 0; i < inGamePlayers.size(); ++i) {
		while (1) {
			card newCard = generateRandomCard();

			if (uniqueCards.size() == 0) {
				uniqueCards.push_back(newCard);
				inGamePlayers[i].cards.push_back(newCard);
				break;
			}

			const auto it = find(
				uniqueCards.begin(),
				uniqueCards.end(),
				newCard
			);

			if (it == uniqueCards.end()) {
				uniqueCards.push_back(newCard);
				inGamePlayers[i].cards.push_back(newCard);
				break;
			}
		}
	}
}

void Calc::addRandomPoolCard(
	cards &poolCards,
	cards &uniqueCards
) {
	while (1) {
		card newCard = generateRandomCard();

		if (uniqueCards.size() == 0) {
			uniqueCards.push_back(newCard);
			poolCards.push_back(newCard);
			return;
		}

		const auto it = find(
			uniqueCards.begin(),
			uniqueCards.end(),
			newCard
		);

		if (it == uniqueCards.end()) {
			uniqueCards.push_back(newCard);
			poolCards.push_back(newCard);
			return;
		}
	}
}

card Calc::generateRandomCard() {
	const vector<string> possibleCardText = {
		"A", "2", "3", "4", "5", "6", "7",
		"8", "9", "10", "J", "Q", "K"
	};
	const vector<const wchar_t *> possibleCardSuit = {
		SPADE, CLUB, HEART, DIAMOND
	};

	string cardText = possibleCardText[rand() % possibleCardText.size()];
	const wchar_t *cardSuit = possibleCardSuit[rand() % possibleCardSuit.size()];

	return make_pair(cardText, cardSuit);
}

cards Calc::getInGamePlayerCards(
	string name,
	vector<InGamePlayer> &inGamePlayers
) {
	const auto it = find_if(
		inGamePlayers.begin(),
		inGamePlayers.end(),
		[name](InGamePlayer p) { return p.name == name; }
	);

	if (it != inGamePlayers.end()) {
		return it->cards;
	}

	return {};
}