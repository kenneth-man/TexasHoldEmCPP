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
    // TODO: figure out how to include windows.h in visual studio and need to conditional
        // include based on OS
    // TODO: Hide input displaying on the screen if a password
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
                static size_t i = 2;
                const size_t maxI = inGamePlayers.size() + 2;

                while(inGameState == Enums::PREFLOPBET) {
                    // TODO: bug if player is small/big blind bet and required to bet again
                    if (i < maxI) {
                        const bool exceededIndex = (i + 1) > inGamePlayers.size();
                        const size_t j = exceededIndex ? i - inGamePlayers.size() : i;
                        const bool isBot = inGamePlayers[j].isBot;

                        if (isBot) {
                            cards availableCards = Misc::joinVectors<cards>(
                                poolCards,
                                inGamePlayers[j].cards
                            );
                            const string action = Calc::calcActionFromCardsStrength(
                                availableCards,
                                inGamePlayers[j],
                                inGamePlayers,
                                gameRank
                            );
                            const uint64_t bet = Calc::calcBetFromAction(
                                inGamePlayers[j],
                                inGamePlayers,
                                gameRank,
                                action
                            );

                            inGamePlayers[j].action = action;
                            inGamePlayers[j].betAmount += bet;
                            inGamePlayers[j].betAmountThisRound += bet;
                            inGamePlayers[j].isDeciding = true;

                            if (inGamePlayers[j].balance <= bet) {
                                inGamePlayers[j].balance = 0;
                                inGamePlayers[j].isTappedOut = true;
                            } else {
                                inGamePlayers[j].balance -= bet;
                            }

                            if (action == "[FOLD]") {
                                inGamePlayers[j].isOut = true;
                            }
                        }

                        const bool playerActionSelected = Draw::inGame(
                            inGamePlayers,
                            inGamePlayers[j],
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

                        if (isBot) {
                            Misc::decision();
                            inGamePlayers[j].isDeciding = false;
                        }

                        if (isBot || playerActionSelected) {
                            ++i;

                            if (i == maxI) {
                                Draw::inGame(
                                    inGamePlayers,
                                    inGamePlayers[j],
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

                                Misc::timer(
                                    3,
                                    Variables::falsyString
                                );
                            }
                        }
                    } else {
                        inGameState = Enums::FLOP;
                    }
                }
                break;
            }
            case Enums::FLOP:
            case Enums::TURN:
            case Enums::RIVER: {
                // TODO: set all in game players betAmountThisRound to 0

                cout << "FLOP, TURN, RIVER switch" << '\n';

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
            case Enums::SHOWDOWN: {
                cout << "SHOWDOWN Not Implemented" << '\n';
                while (1);
                break;
            }
            case Enums::END: {
                // TODO: update player object data to file
                // TODO: stats screen to show updates to their data file before returning to
                    // main menu
                gameState = Enums::TITLE;
                exit = true;
                break;
            }
            case Enums::EARLYEND: {
                gameState = Enums::TITLE;
                exit = true;
                break;
            }
            case Enums::FOLD:
            case Enums::CALL:
            case Enums::RAISE:
            case Enums::BET:
            case Enums::CHECK: {
                Calc::betActionHandle(
                    inGameState,
                    inGameStatePrev,
                    inGamePlayers,
                    player,
                    gameRank
                );
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