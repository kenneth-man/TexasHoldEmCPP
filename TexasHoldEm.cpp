#include <vector>
#include <iostream>
#include "./TexasHoldEm/src/constants/variables.h"
#include "./TexasHoldEm/src/constants/typeAliases.h"
#include "./TexasHoldEm/src/constants/enums.h"
#include "./TexasHoldEm/src/game/calc/calc.h"
#include "./TexasHoldEm/src/game/screens/screens.h"
#include "./TexasHoldEm/src/file/file.h"
#include "./TexasHoldEm/src/misc/misc.h"

int main() {
    Enums::GameState gameState = Enums::AUTH;

    MenuItemsConfig config = Calc::initMenuItems();

    menuItem selectedAuthItem = config.authScreenItems[0];
    menuItem selectedTitleScreenItem = config.titleScreenItems[0];
    menuItem selectedQuitScreenItem = config.quitScreenItems[0];

    while(1) {
        switch(gameState) {
            case Enums::AUTH: {
                Screens::menuScreen(
                    config.authScreenItems,
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
                    config.titleScreenItems,
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
                Screens::menuScreen(
                    config.quitScreenItems,
                    selectedQuitScreenItem,
                    gameState,
                    Variables::quitStateMap,
                    "Are you sure you want to quit?"
                );
                break;
            }
            case Enums::QUIT_0: {
                gameState = Enums::TITLE;
                break;
            }
            case Enums::QUIT_1: {
                Misc::handleExit();
            }
        }
    }
}
