#pragma once

#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>
#include "../game/screens/screens.h"
#include "../constants/variables.h"
#include "../auth/auth.h"

using namespace std;

namespace File {
	void test();
	bool existingUser(string username);
	string updateLineValue(
		string username,
		string prefix,
		string value
	);
	string getLineValue(
		string username,
		string prefix
	);
	string findByPrefix(
		string username,
		string prefix,
		fstream &in
	);
	bool resetUser(string username);
	bool createUser(
		string username,
		string password,
		string key,
		bool passwordAlreadyEncrypted = false
	);
	void updateLeaderboard();
	void updateOptions();
}