#pragma once

#include <map>
#include <unordered_map>
#include <vector>
#include <string>
#include <filesystem>
#include <stdint.h>
#include "./typeAliases.h"
#include "./enums.h"

using namespace std;

namespace Variables {
	// "\x9C" = '£'
	const char up = 'w';
	const char left = 'a';
	const char down = 's';
	const char right = 'd';
	const char select = 'p';
	const char space = ' ';
	const string falsyString = "!";
	const string xBorder = "|";
	const string yBorder = "-";
	// TODO: Option on title screen to set height and width of terminal
		// to re-calc xSizeGameMenu and ySizeGameMenu and inGameMenu
	const int xSize = 120;
	const int ySize = 20;
	const int minPasswordLen = 6;
	const string cardSpace = "   ";
	const string arrow = "<--";
	const string txtFileBasePath = filesystem::current_path()
		.string() +
		"\\TexasHoldem\\res\\";
	const string leaderboard = txtFileBasePath + "leaderboard.txt";
	const string options = txtFileBasePath + "options.txt";
	const int authMenuColAlign = 8;
	const int authMenuRowAlign = 2;
	const int titleMenuColAlign = 8;
	const int titleMenuRowAlign = 4;
	const int quitMenuColAlign = 8;
	const int quitMenuRowAlign = 2;
	const int newGameMenuColAlign = 8;
	const int newGameMenuRowAlign = 2;
	const int rankMenuColAlign = 8;
	const int rankMenuRowAlign = 3;
	const string passwordPrefix = "Password: ";
	const string rankPrefix = "Rank: ";
	const string eloPrefix = "Elo: ";
	const string balancePrefix = "Balance: ";
	const string winsPrefix = "Wins: ";
	const string lossesPrefix = "Losses: ";
	const string gamesPlayedPrefix = "Games Played: ";
	const string texasHoldEm = R"(
 _____                    _   _       _     _ _ _____          
|_   _|                  | | | |     | |   | ( )  ___|         
  | | _____  ____ _ ___  | |_| | ___ | | __| |/| |__ _ __ ___  
  | |/ _ \ \/ / _` / __| |  _  |/ _ \| |/ _` | |  __| '_ ` _ \ 
  | |  __/>  < (_| \__ \ | | | | (_) | | (_| | | |__| | | | | |
  \_/\___/_/\_\__,_|___/ \_| |_/\___/|_|\__,_| \____/_| |_| |_|
	)";
	const string smallBlind = R"(
 _____                 _ _  ______ _ _           _ 
/  ___|               | | | | ___ \ (_)         | |
\ `--. _ __ ___   __ _| | | | |_/ / |_ _ __   __| |
 `--. \ '_ ` _ \ / _` | | | | ___ \ | | '_ \ / _` |
/\__/ / | | | | | (_| | | | | |_/ / | | | | | (_| |
\____/|_| |_| |_|\__,_|_|_| \____/|_|_|_| |_|\__,_|
	)";
	const string bigBlind = R"(
______ _        ______ _ _           _ 
| ___ (_)       | ___ \ (_)         | |
| |_/ /_  __ _  | |_/ / |_ _ __   __| |
| ___ \ |/ _` | | ___ \ | | '_ \ / _` |
| |_/ / | (_| | | |_/ / | | | | | (_| |
\____/|_|\__, | \____/|_|_|_| |_|\__,_|
          __/ |                        
         |___/                         
	)";
	const string win = R"(
 _    _ _         _   _   _  
| |  | (_)       | | | | | | 
| |  | |_ _ __   | | | | | | 
| |/\| | | '_ \  | | | | | | 
\  /\  / | | | | |_| |_| |_| 
 \/  \/|_|_| |_| (_) (_) (_) 
	)";
	const string error = R"(
 _____                    
|  ___|                   
| |__ _ __ _ __ ___  _ __ 
|  __| '__| '__/ _ \| '__|
| |__| |  | | | (_) | |   
\____/_|  |_|  \___/|_|   
	)";
	const string gameOver = R"(
 _____                        _____                            
|  __ \                      |  _  |                           
| |  \/ __ _ _ __ ___   ___  | | | |_   _____ _ __             
| | __ / _` | '_ ` _ \ / _ \ | | | \ \ / / _ \ '__|            
| |_\ \ (_| | | | | | |  __/ \ \_/ /\ V /  __/ |     _   _   _ 
 \____/\__,_|_| |_| |_|\___|  \___/  \_/ \___|_|    (_) (_) (_)
	)";
	// @inGameActions
	const vector<string> inGameActions = {
		"FOLD",
		"CALL",
		"RAISE",
		"BET",
		"CHECK"
	};
	const vector<string> authScreenActions = {
		"[LOGIN]",
		"[REGISTER]"
	};
	const vector<string> titleScreenActions = {
		"[NEW GAME]",
		"[CONTINUE]",
		"[INSTRUCTIONS]",
		"[LEADERBOARD]",
		"[OPTIONS]",
		"[QUIT]"
	};
	const vector<string> yesNoScreenActions = {
		"[NO]",
		"[YES]"
	};
	const vector<string> rankScreenActions = {
		"[IRON]",
		"[BRONZE]",
		"[SILVER]",
		"[GOLD]",
		"[PLATINUM]",
		"[DIAMOND]",
		"[MASTER]",
		"[CHALLENGER]",
	};
	const stateMap authStateMap = {
		{authScreenActions[0], Enums::LOGIN},
		{authScreenActions[1], Enums::REGISTER}
	};
	const stateMap titleStateMap = {
		{titleScreenActions[0], Enums::NEWGAME},
		{titleScreenActions[1], Enums::CONTINUE},
		{titleScreenActions[2], Enums::INSTRUCTIONS},
		{titleScreenActions[3], Enums::LEADERBOARD},
		{titleScreenActions[4], Enums::OPTIONS},
		{titleScreenActions[5], Enums::QUIT}
	};
	const stateMap quitStateMap = {
		{yesNoScreenActions[0], Enums::QUIT_0},
		{yesNoScreenActions[1], Enums::QUIT_1}
	};
	const stateMap newGameStateMap = {
		{yesNoScreenActions[0], Enums::NEWGAME_0},
		{yesNoScreenActions[1], Enums::NEWGAME_1}
	};
	const stateMap rankStateMap = {
		{rankScreenActions[0], Enums::RANKIRON},
		{rankScreenActions[1], Enums::RANKBRONZE},
		{rankScreenActions[2], Enums::RANKSILVER},
		{rankScreenActions[3], Enums::RANKGOLD},
		{rankScreenActions[4], Enums::RANKPLATNIUM},
		{rankScreenActions[5], Enums::RANKDIAMOND},
		{rankScreenActions[6], Enums::RANKMASTER},
		{rankScreenActions[7], Enums::RANKCHALLENGER}
	};
	const map<Enums::GameState, Enums::Rank> gameStateRankMap = {
		{Enums::RANKIRON, Enums::IRON},
		{Enums::RANKBRONZE, Enums::BRONZE},
		{Enums::RANKSILVER, Enums::SILVER},
		{Enums::RANKGOLD, Enums::GOLD},
		{Enums::RANKPLATNIUM, Enums::PLATINUM},
		{Enums::RANKDIAMOND, Enums::DIAMOND},
		{Enums::RANKMASTER, Enums::MASTER},
		{Enums::RANKCHALLENGER, Enums::CHALLENGER}
	};
	const map<Enums::InGameState, string> inGameStateMap = {
		{Enums::SMALLBLINDBET, "SMALL BLIND BET"},
		{Enums::BIGBLINDBET, "BIG BLIND BET"},
		{Enums::DEALING, "DEALING CARDS"},
		{Enums::PREFLOPBET, "PRE FLOP BET"},
		{Enums::FLOP, "FLOP"},
		{Enums::FLOPBET, "FLOP BET"},
		{Enums::TURN, "TURN"},
		{Enums::TURNBET, "TURN BET"},
		{Enums::RIVER, "RIVER"},
		{Enums::RIVERBET, "RIVER BET"},
		{Enums::SHOWDOWN, "SHOWDOWN"}
	};
	const map<Enums::Rank, pair<string, uint32_t>> ranksMap = {
		{Enums::IRON, {"Iron", 1}},
		{Enums::BRONZE, {"Bronze", 100}},
		{Enums::SILVER, {"Silver", 1000}},
		{Enums::GOLD, {"Gold", 10000}},
		{Enums::PLATINUM, {"Platinum", 100000}},
		{Enums::DIAMOND, {"Diamond", 500000}},
		{Enums::MASTER, {"Master", 1000000}},
		{Enums::CHALLENGER, {"Challenger", 2000000}}
	};
	const unordered_map<string, string> newUserDefault = {
		{passwordPrefix, Variables::falsyString},
		{rankPrefix, ranksMap.begin()->second.first},
		{eloPrefix, "1000"},
		{balancePrefix, "25"},
		{winsPrefix, "0"},
		{lossesPrefix, "0"},
		{gamesPlayedPrefix, "0"}
	};
	const authUserInstructions loginInstructions = {
		{"Please enter your username", "The name that was used for registration"},
		{"Please enter your password", "The password that was used for registration"},
		{"Please enter your key", "The integer key used for encryption & decryption"}
	};
	const authUserInstructions registerInstructions = {
		{"Please enter a username", "A name to associate your data with"},
		{"Please enter a password", "The password must be at least " + to_string(minPasswordLen) + " characters long"},
		{"Please enter a key", "The key must be an unsigned integer. Used for encryption & decryption"}
	};
	const vector<string> opponentNames = {
		"Ethan",
		"Sophia",
		"Liam",
		"Olivia",
		"Noah",
		"Emma",
		"Lucas",
		"Ava",
		"Jackson",
		"Mia",
		"Aiden",
		"Isabella",
		"Mason",
		"Charlotte",
		"Elijah"
	};
}