#include <vector>
#include <iostream>
#include "./TexasHoldEm/src/constants/variables.h"
#include "./TexasHoldEm/src/constants/typeAliases.h"
#include "./TexasHoldEm/src/constants/enums.h"
#include "./TexasHoldEm/src/game/calc/calc.h"
#include "./TexasHoldEm/src/game/screens/screens.h"
#include "./TexasHoldEm/src/file/file.h"
#include "./TexasHoldEm/src/misc/misc.h"
#include "./TexasHoldEm/src/player/player.h"

int main() {
    Player player {};
    Enums::GameState gameState = Enums::AUTH;
    Enums::Rank gameRank = Enums::IRON;

    MenuItemsConfig config = Calc::initMenuItems();

    menuItem selectedAuthScreenItem = config.authScreenItems[0];
    menuItem selectedTitleScreenItem = config.titleScreenItems[0];
    menuItem selectedQuitScreenItem = config.quitScreenItems[0];
    menuItem selectedNewGameScreenItem = config.newGameScreenItems[0];
    menuItem selectedRankScreenItem = config.rankScreenItems[0];

    while(1) {
        switch(gameState) {
            case Enums::AUTH: {
                Screens::menuScreen(
                    config.authScreenItems,
                    selectedAuthScreenItem,
                    gameState,
                    Variables::authStateMap
                );
                break;
            }
            case Enums::LOGIN: {
                Auth::loginUser(
                    gameState,
                    player
               );
                break;
            }
            case Enums::REGISTER: {
                Auth::registerUser(
                    gameState,
                    player
                );
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
                Screens::menuScreen(
                    config.newGameScreenItems,
                    selectedNewGameScreenItem,
                    gameState,
                    Variables::newGameStateMap,
                    "Are you sure you want to start a new game? All saved data will be reset"
                );
                break;
            }
            case Enums::NEWGAME_0: {
                gameState = Enums::TITLE;
                break;
            }
            case Enums::NEWGAME_1: {
                //reset user data to default

                Screens::menuScreen(
                    config.rankScreenItems,
                    selectedRankScreenItem,
                    gameState,
                    Variables::rankStateMap
                );
                break;
            }
            case Enums::CONTINUE: {
                cout << "CONTINUE Not Implemented" << '\n';
                while (1);
                break;
            }
            case Enums::RANKIRON:
            case Enums::RANKBRONZE:
            case Enums::RANKSILVER:
            case Enums::RANKGOLD:
            case Enums::RANKPLATNIUM:
            case Enums::RANKDIAMOND:
            case Enums::RANKMASTER:
            case Enums::RANKCHALLENGER: {
                Enums::Rank r = Variables::gameStateRankMap.at(gameState);
                gameRank = r;

                break;
            }
            case Enums::INGAME: {
                cout << "INGAME Not Implemented" << '\n';
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
