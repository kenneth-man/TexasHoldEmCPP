#pragma once

#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <set>
#include <conio.h>
#include <stdint.h>
#include <stdlib.h>
#include "typeAliases.h"
#include "variables.h"
#include "structs.h"
#include "enums.h"
#include "draw.h"
#include "screens.h"
#include "inGamePlayer.h"
#include "Player.h"
#include "macros.h"
#include "misc.h"

// forward declaration to prevent circular dependencies
struct Player;

using namespace std;

namespace Calc {
	MenuItemsConfig initMenuItems();
	InGameMenuItemsConfig initInGameMenuItems();
	vector<InGamePlayer> initInGamePlayers(
		string playerName,
		uint64_t playerBalance,
		Enums::Rank gameRank
	);
	vector<menuItem> menuItems(
		const vector<string> &actions,
		uint32_t colAlign,
		uint32_t rowAlign,
		uint32_t xSize = Variables::xSize,
		uint32_t ySize = Variables::ySize
	);
	Enums::MenuAction menuAction(
		const vector<menuItem> &items,
		menuItem &selectedItem
	);
	bool menuValidKeyPressed(char keyPressed);
	vector<menuItem>::iterator menuActionIt(
		const vector<menuItem> &items,
		vector<menuItem> &moveToItems,
		char keyPressed,
		uint32_t xSelected,
		uint32_t ySelected
	);
	void blindBetHandle(
		Player &player,
		vector<InGamePlayer> &inGamePlayers,
		Enums::Rank gameRank,
		Enums::InGameState &inGameState
	);
	string checkInputIsValidUInt(
		string input
	);
	void addRandomPlayerCard(
		vector<InGamePlayer> &inGamePlayers,
		cards &uniqueCards
	);
	void addRandomPoolCard(
		cards &poolCards,
		cards &uniqueCards
	);
	card generateRandomCard();
	cards getInGamePlayerCards(
		string name,
		const vector<InGamePlayer> &inGamePlayers
	);
	Enums::Archetype getRandomArchetype();
	uint64_t getRandomBalance(Enums::Rank rank);
	string getRandomBetAction(
		bool includeFold,
		bool noBetsThisRound
	);
	string calcActionFromCardsStrength(
		const cards &c,
		const InGamePlayer &currentInGamePlayer,
		const vector<InGamePlayer> &inGamePlayers,
		Enums::Rank rank
	); // possible return values @standardBetActions
	uint64_t calcBetFromAction(
		const InGamePlayer &currentInGamePlayer,
		const vector<InGamePlayer> &inGamePlayers,
		Enums::Rank rank,
		string action
	);
	Enums::CardsStrength findCardsStrength(
		const cards &c
	);
	void betActionHandle(
		Enums::InGameState &inGameState,
		Enums::InGameState inGameStatePrev,
		vector<InGamePlayer> &inGamePlayers,
		const Player &player,
		Enums::Rank gameRank
	);
	void betActionUpdate(
		vector<InGamePlayer>::iterator &inGamePlayerIt,
		uint64_t valueToAdd,
		string insufficientFundsError
	);
	//TODO: ELO CALCULATION/S
}