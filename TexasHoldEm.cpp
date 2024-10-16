﻿#include <vector>
#include <iostream>
#include <stdlib.h>
#include "variables.h"
#include "typeAliases.h"
#include "enums.h"
#include "calc.h"
#include "screens.h"
#include "file.h"
#include "misc.h"
#include "player.h"

int main() {
    srand((uint32_t)time(NULL));

    Player player {};
    vector<InGamePlayer> inGamePlayers {};
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
                bool success = File::resetUser(player.name);
                if (!success) {
                    Screens::errorScreen("Error creating a new game");
                    gameState = Enums::TITLE;
                    break;
                }
                player.init(player.name);
                Screens::menuScreen(
                    config.rankScreenItems,
                    selectedRankScreenItem,
                    gameState,
                    Variables::rankStateMap
                );
                break;
            }
            case Enums::CONTINUE: {
                Screens::menuScreen(
                    config.rankScreenItems,
                    selectedRankScreenItem,
                    gameState,
                    Variables::rankStateMap
                );
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
                Enums::Rank rank = Variables::gameStateRankMap.at(gameState);
                if (player.balance < Variables::ranksBetRangeMap.at(rank).second.first) {
                    Screens::errorScreen(
                        "You do not have sufficient funds to make a minimum bet "
                        "at this rank"
                    );
                    gameState = Enums::TITLE;
                    break;
                }
                gameRank = rank;
                inGamePlayers = Calc::initInGamePlayers(
                    player.name,
                    player.balance,
                    gameRank
                );
                Misc::handleEnteringGame();
                gameState = Enums::INGAME;
                break;
            }
            case Enums::INGAME: {
                Screens::inGameScreen(
                    player,
                    inGamePlayers,
                    gameState,
                    gameRank
                );
                break;
            }
            case Enums::LEADERBOARD: {
                cout << "LEADERBOARD Not Implemented" << '\n';
                while (1);
                break;
            }
            case Enums::INSTRUCTIONS: {
                Screens::instructionScreen(gameState);
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
