#pragma once

#include <fstream>
#include <filesystem>
#include <string>
#include <iostream>
#include "screens.h"
#include "variables.h"
#include "auth.h"

using namespace std;

namespace File {
	void test();
	void openUserFStream(
		fstream &stream,
		ios_base::openmode mode,
		string username
	);
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