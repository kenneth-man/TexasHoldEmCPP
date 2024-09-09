#include "screens.h"

string Screens::infoScreen(
    string description,
    string hint,
    bool quit
) {
    Draw::title();
    Draw::text(description);
    Draw::text("(" + hint + ")");
    if (quit) {
        Draw::text("(Or submit '" + Variables::quit + "' to go back)");
    }
    string input;
    // not using `cin << input`, as it will ignore spaces
    getline(cin, input);
    return input;
}

void Screens::errorScreen(string description) {
    system("CLS");
    Draw::text(Variables::error);
    Draw::text(description);
    Draw::text("(Enter any key to Continue...)");
    // typecast to void, to suppress warning 'Return Value Ignored...'
    (void)_getch();
}

void Screens::menuScreen(
    const vector<menuItem> &menuItems,
    menuItem &selectedItem,
    Enums::GameState &gameState,
    const gameStateMap &stateMap,
    string hint
) {
    Draw::title();

    if (hint != Variables::falsyString) {
        Draw::text("(" + hint + ")");
    }

    Draw::menu(
        menuItems,
        selectedItem
    );

    if (
        Calc::menuAction(
            menuItems,
            selectedItem
        ) == Enums::SELECT
    ) {
        auto it = stateMap.find(selectedItem.first);

        if (it != stateMap.end()) {
            gameState = it->second;
            return;
        }

        errorScreen("Incorrect Map of actions to enums");
    }
}

void Screens::inGameScreen(
    Player &player,
    vector<InGamePlayer> &inGamePlayers,
    Enums::GameState &gameState,
    Enums::Rank gameRank
) {
    bool exit = false;
    cards poolCards = {};
    cards uniqueCards = {};
    InGameMenuItemsConfig config = Calc::initInGameMenuItems();
    menuItem selectedPreflopBetItem = config.preflopBetItems[0];
    menuItem selectedStandardBetItem = config.standardBetItems[0];
    Enums::InGameState inGameState = Enums::SMALLBLINDBET;
    Enums::InGameState inGameStatePrev = Enums::SMALLBLINDBET;

    while(!exit) {
        switch(inGameState) {
            case Enums::SMALLBLINDBET: {
                Calc::blindBetHandle(
                    player,
                    inGamePlayers,
                    gameRank,
                    inGameState
                );
                break;
            }
            case Enums::BIGBLINDBET: {
                Calc::blindBetHandle(
                    player,
                    inGamePlayers,
                    gameRank,
                    inGameState
                );
                break;
            }
            case Enums::DEALING: {
                for (uint8_t i = 0; i < 2; ++i) {
                    Calc::addRandomPlayerCard(
                        inGamePlayers,
                        uniqueCards
                    );
                }
                inGameState = Enums::PREFLOPBET;
                break;
            }
            case Enums::PREFLOPBET: {
                inGameStatePrev = Enums::PREFLOPBET;
                // TODO: reset to 2 on game completion
                static uint8_t i = 2;

                while(inGameState == Enums::PREFLOPBET) {
                    if (i < inGamePlayers.size() + 2) {
                        if (inGamePlayers[i].isBot) {
                            cards availableCards = Misc::joinVectors<cards>(
                                poolCards,
                                inGamePlayers[i].cards
                            );
                            const string action = Calc::calcActionFromCardsStrength(
                                availableCards,
                                inGamePlayers[i],
                                inGamePlayers,
                                gameRank
                            );
                            const uint64_t bet = Calc::calcBetFromAction(
                                inGamePlayers[i],
                                inGamePlayers,
                                gameRank,
                                action
                            );
                            inGamePlayers[i].action = action;
                            inGamePlayers[i].betAmount += bet;
                            inGamePlayers[i].balance -= bet;
                            inGamePlayers[i].isDeciding = true;
                        }

                        Draw::inGame(
                            inGamePlayers,
                            inGamePlayers[i],
                            inGameState,
                            poolCards,
                            Calc::getInGamePlayerCards(
                                player.name,
                                inGamePlayers
                            ),
                            selectedPreflopBetItem,
                            config.preflopBetItems,
                            Variables::preflopBetActionsStateMap
                        );

                        if (inGamePlayers[i].isBot) {
                            Misc::decision();
                            inGamePlayers[i].isDeciding = false;
                        }

                        ++i;
                    } else {
                        inGameState = Enums::FLOP;
                    }
                }
                break;
            }
            case Enums::FLOP: {
                cout << "FLOP Not Implemented" << '\n';

                /*for (uint8_t i = 0; i < 3; ++i) {
                    Calc::addRandomPoolCard(
                        poolCards,
                        uniqueCards
                    );
                }*/

                while (1);
                break;
            }
            case Enums::FLOPBET:
            case Enums::TURNBET: 
            case Enums::RIVERBET: {
                cout << "FLOPBET, TURNBET, RIVERBET Not Implemented" << '\n';
                while (1);
                break;
            }
            case Enums::TURN: {
                cout << "TURN Not Implemented" << '\n';
                while (1);
                break;
            }
            case Enums::RIVER: {
                cout << "RIVER Not Implemented" << '\n';
                while (1);
                break;
            }
            case Enums::SHOWDOWN: {
                cout << "SHOWDOWN Not Implemented" << '\n';
                while (1);
                break;
            }
            case Enums::END: {
                // update player data in file
                // update player object in ram
                // update game state
                // screen to show updates to their data file
                gameState = Enums::TITLE;
                exit = true;
                break;
            }
            case Enums::EARLYEND: {
                gameState = Enums::TITLE;
                exit = true;
                break;
            }
            case Enums::FOLD: {
                cout << "FOLD Not Implemented" << '\n';
                // inGameState = inGameStatePrev; put inside a reusable function
                while (1);
                break;
            }
            case Enums::CALL: {
                cout << "CALL Not Implemented" << '\n';
                // inGameState = inGameStatePrev; put inside a reusable function
                while (1);
                break;
            }
            case Enums::RAISE: {
                cout << "RAISE Not Implemented" << '\n';
                // inGameState = inGameStatePrev; put inside a reusable function
                while (1);
                break;
            }
            case Enums::BET: {
                cout << "BET Not Implemented" << '\n';
                // inGameState = inGameStatePrev; put inside a reusable function
                while (1);
                break;
            }
            case Enums::CHECK: {
                cout << "CHECK Not Implemented" << '\n';
                // inGameState = inGameStatePrev; put inside a reusable function
                while (1);
                break;
            }
        }
    }
}

void Screens::instructionScreen(Enums::GameState &gameState) {
    Draw::title();
    Draw::text(Variables::instructions);
    const string info = "submit '" + Variables::quit + "' to go back";
    Draw::text("(" + info + ")");

    string input;
    getline(cin, input);

    if (input == Variables::quit) {
        gameState = Enums::TITLE;
        return;
    }

    Screens::errorScreen("Invalid Key Pressed. " + info);
}