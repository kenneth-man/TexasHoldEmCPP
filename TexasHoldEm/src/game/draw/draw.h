#pragma once

#include <io.h>
#include <fcntl.h>
#include <iostream>
#include <vector>
#include <stdint.h>
#include "player.h"
#include "inGamePlayer.h"
#include "variables.h"
#include "typeAliases.h"

using namespace std;

namespace Draw {
	void text(
		string t,
		bool border = false
	);
	void menu(
		const vector<menuItem> &items,
		const menuItem &selectedItem,
		uint16_t xSize = Variables::xSize,
		uint16_t ySize = Variables::ySize
	);
	void inGame(
		const vector<InGamePlayer> &inGamePlayers,
		string currentInGamePlayer,
		Enums::InGameState inGameState,
		const cards &poolCards,
		const cards &playerCards
	);
	void list(
		const vector<InGamePlayer> &inGamePlayers,
		string currentInGamePlayer,
		Enums::InGameState inGameState
	);
	void playingCards(
		const cards &poolCards,
		const cards &playerCards
	);
	string border(
		uint16_t col,
		uint16_t row,
		uint16_t xSize,
		uint16_t ySize
	);
	void title();
	void wideChar(
		const wchar_t *hexChar,
		bool lineBreak = false
	);
	void cardRow(
		const vector<string> &vals,
		const vector<const wchar_t *> &suitHexChars // possible values @suitHexChars
	);
	void cardRowVals(const vector<string> &vals);
	void cardRowWChars(
		const vector<const wchar_t *> &suitHexChars  // possible values @suitHexChars
	);
}