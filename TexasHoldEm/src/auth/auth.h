#pragma once

#include <fstream>
#include <string>
#include <stdexcept>
#include "../game/screens/screens.h"
#include "../file/file.h"
#include "../constants/enums.h"
#include "../constants/variables.h"
#include "../player/player.h"

// forward declaration to prevent circular depedencies
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
		string (*validation)(string, int)
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
		int index
	);
	string registerUserValidation(
		string input,
		int index
	);
	void failure(
		string error,
		Enums::GameState &gameState
	);
}