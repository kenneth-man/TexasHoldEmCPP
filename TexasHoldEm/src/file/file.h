#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include "../game/screens/screens.h"
#include "../constants/variables.h"
#include "../auth/auth.h"

using namespace std;

namespace File {
	void test();
	bool existingUser(string username);
	void getUser();
	bool createUser(
		string username,
		string password,
		string key
	);
	void updateLeaderboard();
	void updateOptions();
}