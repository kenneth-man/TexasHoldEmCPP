#pragma once

#include <map>
#include <vector>
#include <string>
#include "./enums.h"

using namespace std;

using menuItem = pair<string, vector<int>>;
using stateMap = map<string, Enums::GameState>;
using authUserInstructions = vector<pair<string, string>>;