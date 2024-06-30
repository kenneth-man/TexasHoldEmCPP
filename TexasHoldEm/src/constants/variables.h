#pragma once

#include <map>
#include <vector>
#include <string>
#include <filesystem>
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
	const string passwordPrefix = "Password: ";
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
}