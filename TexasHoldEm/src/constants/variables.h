#pragma once

#include <map>
#include <vector>
#include <string>
#include "./typeAliases.h"

using namespace std;

namespace Variables {
	// "\x9C" = '£'
	const char up = 'w';
	const char left = 'a';
	const char down = 's';
	const char right = 'd';
	const char select = 'p';
	const char space = ' ';
	const char falsy = '!';
	const string falsyString = "!";
	const string xBorder = "|";
	const string yBorder = "-";
	// TODO: Option on title screen to set height and width of terminal
		// to re-calc xSizeGameMenu and ySizeGameMenu and inGameMenu
	const int xSize = 120;
	const int ySize = 20;
	const string arrow = "<--";
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
	const vector<string> titleScreenActions = {
		"NEW GAME",
		"CONTINUE",
		"INSTRUCTIONS",
		"LEADERBOARD",
		"OPTIONS",
		"QUIT"
	};
}