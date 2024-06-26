﻿#include <vector>
#include <iostream>
#include "./TexasHoldEm/src/constants/variables.h"
#include "./TexasHoldEm/src/constants/typeAliases.h"
#include "./TexasHoldEm/src/constants/enums.h"
#include "./TexasHoldEm/src/game/calc/calc.h"
#include "./TexasHoldEm/src/game/screens/screens.h"
#include "./TexasHoldEm/src/file/file.h"

int main() {
    Enums::GameState gameState = Enums::AUTH;

    const vector<menuItem> authMenuItems = Calc::menuItems(
        Variables::authScreenActions,
        Variables::authMenuColAlign,
        Variables::authMenuRowAlign
    );
    const vector<menuItem> titleScreenMenuItems = Calc::menuItems(
        Variables::titleScreenActions,
        Variables::titleMenuColAlign,
        Variables::titleMenuRowAlign
    );

    menuItem selectedAuthItem = authMenuItems[0];
    menuItem selectedTitleScreenItem = titleScreenMenuItems[0];

    while(1) {
        switch(gameState) {
            case Enums::AUTH: {
                Screens::menuScreen(
                    authMenuItems,
                    selectedAuthItem,
                    gameState,
                    Variables::authStateMap
                );
                break;
            }
            case Enums::LOGIN: {
                Auth::loginUser(gameState);
                break;
            }
            case Enums::REGISTER: {
                Auth::registerUser(gameState);
                break;
            }
            case Enums::TITLE: {
                Screens::menuScreen(
                    titleScreenMenuItems,
                    selectedTitleScreenItem,
                    gameState,
                    Variables::titleStateMap
                );
                break;
            }
            case Enums::NEWGAME: {
                cout << "NEWGAME Not Implemented" << '\n';
                while (1);
                break;
            }
            case Enums::CONTINUE: {
                cout << "CONTINUE Not Implemented" << '\n';
                while (1);
                break;
            }
            case Enums::LEADERBOARD: {
                cout << "LEADERBOARD Not Implemented" << '\n';
                while (1);
                break;
            }
            case Enums::INSTRUCTIONS: {
                cout << "INSTRUCTIONS Not Implemented" << '\n';
                while (1);
                break;
            }
            case Enums::OPTIONS: {
                cout << "OPTIONS Not Implemented" << '\n';
                while (1);
                break;
            }
            case Enums::QUIT: {
                cout << "QUIT Not Implemented" << '\n';
                while (1);
            }
        }
    }
}
