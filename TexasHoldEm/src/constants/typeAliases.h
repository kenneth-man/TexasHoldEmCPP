#pragma once

#include <map>
#include <vector>
#include <string>
#include <stdint.h>
#include "enums.h"

using namespace std;

using menuItem = pair<string, vector<uint32_t>>;
using gameStateMap = map<string, Enums::GameState>;
using inGameStateMap = map<string, Enums::InGameState>;
using authUserInstructions = vector<pair<string, string>>;
// `const wchar_t *` possible values @suitHexChars
using card = pair<string, const wchar_t *>;
using cards = vector<card>;
using rankBetRange = pair<string, pair<uint64_t, uint64_t>>;