#include "calc.h"

////////////////////////////////////////////////////////////////////////////////////
// static methods - these cannot be called outside this file
////////////////////////////////////////////////////////////////////////////////////
static cards checkAtleastFiveCardsSameSuit(const cards &c) {
	vector<cards> suitsCount = {{}, {}, {}, {}};

	for (auto &card : c) {
		if (card.second == SPADE) {
			suitsCount[0].push_back(card);
			continue;
		}
		if (card.second == CLUB) {
			suitsCount[1].push_back(card);
			continue;
		}
		if (card.second == HEART) {
			suitsCount[2].push_back(card);
			continue;
		}
		if (card.second == DIAMOND) {
			suitsCount[3].push_back(card);
			continue;
		}
	}

	for (uint8_t i = 0; i < suitsCount.size(); ++i) {
		if (suitsCount[i].size() >= 5) {
			return suitsCount[i];
		}
	}

	return {};
}

static bool checkRoyalFlush(const cards &c) {
	if (c.size() == 2) {
		auto royalFlushCard1It = find(
			Variables::royalFlushCards.begin(),
			Variables::royalFlushCards.end(),
			c[0].first
		);
		auto royalFlushCard2It = find(
			Variables::royalFlushCards.begin(),
			Variables::royalFlushCards.end(),
			c[1].first
		);

		if (
			royalFlushCard1It != Variables::royalFlushCards.end() &&
			royalFlushCard2It != Variables::royalFlushCards.end()
			) {
			return true;
		}

		return false;
	} else {
		set<string> cardValueMatches = {};

		for (auto &crd : c) {
			auto it = find(
				Variables::royalFlushCards.begin(),
				Variables::royalFlushCards.end(),
				crd.first
			);

			if (it != Variables::royalFlushCards.end()) {
				cardValueMatches.insert(crd.first);
			}
		}

		if (cardValueMatches.size() == Variables::royalFlushCards.size()) {
			return true;
		}

		return false;
	}
}

static void correctCardLetterTenOrder(vector<string> &uniqueCardValuesVec) {
	const auto cardLetterTenIt = find(
		uniqueCardValuesVec.begin(),
		uniqueCardValuesVec.end(),
		Variables::orderOfCards[8]
	);

	if (cardLetterTenIt != uniqueCardValuesVec.end()) {
		uniqueCardValuesVec.erase(cardLetterTenIt);
		uniqueCardValuesVec.push_back(Variables::orderOfCards[8]);
	}
}

static void findCardIndexes(
	uint8_t &card1Index,
	uint8_t &card2Index,
	const cards &c
) {
	for (uint8_t i = 0; i < Variables::orderOfCards.size(); ++i) {
		if (Variables::orderOfCards[i] == c[0].first) {
			card1Index = i;
		}
		if (Variables::orderOfCards[i] == c[1].first) {
			card2Index = i;
		}
	}
}

static vector<string> setUniqueCardValuesVec(const set<string> &uniqueCardValues) {
	set<string> removedCardLetters;
	bool jack = false;
	bool queen = false;
	bool king = false;
	bool ace = false;
	uint8_t cardLetterIndexBegin = 9;

	for (auto &c : uniqueCardValues) {
		if (c == Variables::orderOfCards[cardLetterIndexBegin]) {
			jack = true;
			continue;
		}
		if (c == Variables::orderOfCards[cardLetterIndexBegin + 1]) {
			queen = true;
			continue;
		}
		if (c == Variables::orderOfCards[cardLetterIndexBegin + 2]) {
			king = true;
			continue;
		}
		if (c == Variables::orderOfCards[cardLetterIndexBegin + 3]) {
			ace = true;
			continue;
		}

		removedCardLetters.insert(c);
	}

	// std::copy needs to know how much space to accommodate for the elements
		// being copied; that's why a vector size() is defined
	vector<string> uniqueCardValuesVec(removedCardLetters.size());
	vector<bool> cardLetters{jack, queen, king, ace};

	copy(
		removedCardLetters.begin(),
		removedCardLetters.end(),
		uniqueCardValuesVec.begin()
	);

	correctCardLetterTenOrder(uniqueCardValuesVec);

	for (uint8_t i = 0; i < cardLetters.size(); ++i) {
		if (cardLetters[i]) {
			uniqueCardValuesVec.push_back(
				Variables::orderOfCards[i + cardLetterIndexBegin]
			);
		}
	}

	return uniqueCardValuesVec;
}

static bool checkStartingAce(
	uint8_t card1Index,
	uint8_t card2Index
) {
	return (card1Index == 0 && card2Index == Variables::orderOfCards.size() - 1) ||
		(card2Index == 0 && card1Index == Variables::orderOfCards.size() - 1);
}

static bool checkStraight(const cards &c) {
	if (c.size() == 2) {
		uint8_t card1Index {};
		uint8_t card2Index {};

		findCardIndexes(
			card1Index,
			card2Index,
			c
		);

		uint8_t indexDiff = abs(card1Index - card2Index);

		if (
			(indexDiff <= 4 && indexDiff > 0) ||
			checkStartingAce(card1Index, card2Index)
		) {
			return true;
		}

		return false;
	} else {
		set<string> uniqueCardValues = {};

		for (auto &crd : c) {
			uniqueCardValues.insert(crd.first);
		}

		if (uniqueCardValues.size() < 5) {
			return false;
		}

		uint8_t consecutiveCards = 0;
		vector<string> uniqueCardValuesVec = setUniqueCardValuesVec(
			uniqueCardValues
		);

		for (uint8_t i = 0; i < uniqueCardValuesVec.size(); ++i) {
			uint8_t card1Index {};
			uint8_t card2Index {};

			if (i < uniqueCardValuesVec.size() - 1) {
				findCardIndexes(
					card1Index,
					card2Index,
					{
						{uniqueCardValuesVec[i], FALSYCHARMAP},
						{uniqueCardValuesVec[i + 1], FALSYCHARMAP}
					}
				);

				if (
					i == 0 &&
					uniqueCardValuesVec[i] == Variables::orderOfCards[0] &&
					*(uniqueCardValuesVec.end() - 1) ==
						*(Variables::orderOfCards.end() - 1)
				) {
					consecutiveCards++;
				}

				uint8_t indexDiff = abs(card1Index - card2Index);

				if (indexDiff == 1) {
					consecutiveCards++;

					if (consecutiveCards >= 4) {
						return true;
					}
				} else {
					consecutiveCards = 0;
				}
			}
		}

		return false;
	}
}

static uint8_t checkCardLetter(string s) {
	try {
		uint8_t i = stoi(s);
		return i;
	} catch (const invalid_argument &_) {
		uint8_t jackQueenKingOrAce = 255;
		return jackQueenKingOrAce;
	}
}

static bool checkOfAKind(
	const cards &c,
	Enums::CardsStrength s
) {
	map<string, uint8_t> cardCounts = {};

	for (auto &crd : c) {
		try {
			uint8_t count = cardCounts.at(crd.first);
			cardCounts.erase(crd.first);
			cardCounts.emplace(crd.first, count + 1);
		} catch (const out_of_range &_) {
			cardCounts.emplace(crd.first, 1);
		}
	}

	if (
		find_if(
			cardCounts.begin(),
			cardCounts.end(),
			[s](pair<string, uint8_t> count) {
				switch (s) {
					case Enums::FOUROFAKIND: {
						return count.second == 4;
					}
					case Enums::FULLHOUSE: {
						static string threeOfAKindCard = Variables::falsyString;
						static string twoOfAKindCard = Variables::falsyString;

						if (count.second == 3) {
							threeOfAKindCard = count.first;
						} else if (count.second == 2) {
							twoOfAKindCard = count.first;
						}

						return threeOfAKindCard != Variables::falsyString &&
							twoOfAKindCard != Variables::falsyString;
					}
					case Enums::THREEOFAKIND: {
						return count.second == 3;
					}
					case Enums::TWOPAIR: {
						static uint8_t pairCount = 0;
						if (count.second == 2) {
							pairCount++;
						}
						return pairCount == 2;
					}
					case Enums::PAIR: {
						return count.second == 2;
					}
					default: return false;
				}
			}
		) != cardCounts.end()
	) {
		return true;
	}
	return false;
}

static bool checkHighCard(const cards &c) {
	for (auto &crd : c) {
		if (checkCardLetter(crd.first) > 9) {
			return true;
		}
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

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

vector<InGamePlayer> Calc::initInGamePlayers(
	string playerName,
	uint64_t playerBalance,
	Enums::Rank gameRank
) {
	vector<InGamePlayer> output;
	vector<string> names = Variables::opponentNames;

	while (output.size() < Variables::maxPlayers) {
		size_t index = rand() % names.size();

		output.push_back({
			names[index],
			0,
			Calc::getRandomBalance(gameRank),
			{},
			Variables::falsyString,
			true,
			true,
			false,
			Calc::getRandomArchetype()
		});

		names.erase(names.begin() + index);
	}

	size_t playerIndex = rand() % output.size();
	output.at(playerIndex) = {
		playerName,
		0,
		playerBalance,
		{},
		Variables::falsyString,
		false,
		true,
		false,
		Enums::HUMAN
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

Enums::MenuAction Calc::menuAction(
	const vector<menuItem> &items,
	menuItem &selectedItem
) {
	const uint32_t x = selectedItem.second[0];
	const uint32_t y = selectedItem.second[1];
	vector<menuItem> moveToItems;

	char input = _getch();
	char keyPressed = tolower(input);

	if (!menuValidKeyPressed(keyPressed)) {
		return Enums::INVALID;
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
			return Enums::CHANGE;
		}
		case Variables::down:
		case Variables::right: {
			if (it == --moveToItems.end()) {
				selectedItem = *(moveToItems.begin());
			} else {
				selectedItem = *(++it);
			}
			return Enums::CHANGE;
		}
		case Variables::select: {
			return Enums::SELECT;
		}
		case Variables::toggleView: {
			return Enums::TOGGLEVIEW;
		}
		default: return Enums::INVALID;
	}
}

bool Calc::menuValidKeyPressed(char keyPressed) {
	switch(keyPressed) {
		case Variables::up:
		case Variables::down:
		case Variables::left:
		case Variables::right:
		case Variables::select:
		case Variables::toggleView:
			return true;
		default:
			Screens::errorScreen("Invalid Key Pressed");
			return false;
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
		uint64_t bet = rand() % range.second.second;
		if (inGameState == Enums::SMALLBLINDBET) {
			inGamePlayers[inGameState].betAmount = bet == 0 ?
				range.second.first :
				bet;
			inGamePlayers[inGameState].action = Variables::miscBetActions[0];
			inGameState = Enums::BIGBLINDBET;
		} else {
			const uint64_t diff = range.second.second - inGamePlayers[0].betAmount;
			while(bet < inGamePlayers[0].betAmount) {
				bet = diff == 0 ?
					range.second.second :
					rand() % diff + inGamePlayers[0].betAmount;
			}
			inGamePlayers[inGameState].betAmount = bet;
			inGamePlayers[inGameState].action = Variables::miscBetActions[1];
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
			inGamePlayers[inGameState].action = Variables::miscBetActions[0];
			inGamePlayers[inGameState].betAmount = bet;
			inGamePlayers[inGameState].balance -= bet;
			player.balance -= bet;
			File::updateLineValue(
				player.name,
				Variables::balancePrefix,
				to_string(player.balance)
			);
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
			inGamePlayers[inGameState].action = Variables::miscBetActions[0];
			inGamePlayers[inGameState].betAmount = bet;
			inGamePlayers[inGameState].balance -= bet;
			player.balance -= bet;
			File::updateLineValue(
				player.name,
				Variables::balancePrefix,
				to_string(player.balance)
			);
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
		const int64_t i = stoi(input);

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
		return "Key exceeds the max number of a 8 byte integer";
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
	const vector<InGamePlayer> &inGamePlayers
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

Enums::Archetype Calc::getRandomArchetype() {
	uint64_t num = Misc::randomInt(
		Enums::PASSIVE,
		Enums::AGGRESSIVE
	);

	switch (num) {
		case Enums::PASSIVE: {
			return Enums::PASSIVE;
		}
		case Enums::NEUTRAL: {
			return Enums::NEUTRAL;
		}
		case Enums::AGGRESSIVE: {
			return Enums::AGGRESSIVE;
		}
		default: {
			return Enums::NEUTRAL;
		}
	}
}

uint64_t Calc::getRandomBalance(
	Enums::Rank rank
) {
	rankBetRange betRange = Variables::ranksBetRangeMap.at(rank);
	pair<uint64_t, uint64_t> range = betRange.second;
	uint64_t diff = range.second - range.first;
	return (Misc::randomInt(range.first, diff) + range.second) * 3;
}

Enums::InGameState Calc::calcActionFromCardsStrength(
	const cards &c,
	Enums::Archetype archetype,
	Enums::Rank rank,
	const inGameStateMap &possibleActions
) {
	switch(c.size()) {
		case 2: {
			return Enums::FOLD;
		}
		case 5: {
			return Enums::FOLD;
		}
		case 6: {
			return Enums::FOLD;
		}
		case 7: {
			return Enums::FOLD;
		}
		default: return Enums::FOLD;
	}
}

Enums::CardsStrength Calc::findCardsStrength(const cards &c) {
	if (c.size() == 2) {
		if (c[0].second == c[1].second) {
			if (checkRoyalFlush(c)) {
				return Enums::ROYALFLUSH;
			}

			if (checkStraight(c)) {
				return Enums::STRAIGHTFLUSH;
			}

			return Enums::FLUSH;
		}

		if (checkStraight(c)) {
			return Enums::STRAIGHT;
		}

		if (c[0].first == c[1].first) {
			return Enums::PAIR;
		}
	} else {
		cards sameSuit = checkAtleastFiveCardsSameSuit(c);

		if (sameSuit.size()) {
			if (checkRoyalFlush(sameSuit)) {
				return Enums::ROYALFLUSH;
			}
			
			if (checkStraight(sameSuit)) {
				return Enums::STRAIGHTFLUSH;
			}

			return Enums::FLUSH;
		}

		if (checkOfAKind(c, Enums::FOUROFAKIND)) {
			return Enums::FOUROFAKIND;
		}

		if (checkOfAKind(c, Enums::FULLHOUSE)) {
			return Enums::FULLHOUSE;
		}
		
		if (checkStraight(c)) {
			return Enums::STRAIGHT;
		}

		if (checkOfAKind(c, Enums::THREEOFAKIND)) {
			return Enums::THREEOFAKIND;
		}

		if (checkOfAKind(c, Enums::TWOPAIR)) {
			return Enums::TWOPAIR;
		}

		if (checkOfAKind(c, Enums::PAIR)) {
			return Enums::PAIR;
		}
	}

	if (checkHighCard(c)) {
		return Enums::HIGHCARD;
	}

	return Enums::SHOULDNOTPLAY;
}
