#pragma once

#include <fstream>
#include <iostream>
#include "../game/screens/screens.h"
#include "../constants/variables.h"

using namespace std;

namespace File {
	void test();
	void createBaseFiles();
	void getPassword();
	void setCredentials();
	void updateCredentials();
	void updateLeaderboard();
	void updateOptions();
}