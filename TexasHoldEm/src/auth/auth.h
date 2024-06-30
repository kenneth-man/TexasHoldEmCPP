#pragma once

#include <fstream>
#include <string>
#include <stdexcept>
#include "../game/screens/screens.h"
#include "../file/file.h"
#include "../constants/enums.h"
#include "../constants/variables.h"

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
	void loginUser(Enums::GameState &gameState);
	void registerUser(Enums::GameState &gameState);
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