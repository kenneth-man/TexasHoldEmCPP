#pragma once

#include <fstream>
#include <string>
#include <stdexcept>
#include <stdint.h>
#include "screens.h"
#include "file.h"
#include "enums.h"
#include "variables.h"
#include "player.h"

// forward declaration to prevent circular dependencies
// `player.h` includes `file.h`, which includes this file
struct Player;

using namespace std;

namespace Auth {
	string crypt(
		string password,
		string key,
		Enums::Crypt type
	);
	string handleInput(
		vector<string> &inputs,
		const authUserInstructions &instructions,
		string (*validation)(string, uint8_t)
	);
	void loginUser(
		Enums::GameState &gameState,
		Player &player
	);
	void registerUser(
		Enums::GameState &gameState,
		Player &player
	);
	string loginUserValidation(
		string input,
		uint8_t index
	);
	string registerUserValidation(
		string input,
		uint8_t index
	);
	void failure(
		string error,
		Enums::GameState &gameState
	);
}