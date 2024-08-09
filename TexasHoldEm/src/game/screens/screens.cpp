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
        )
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
                // TODO
                // need a function to loop per player, starting with 2 index if PREFLOPBET
                    // (the player after the big blind bet player)
                // need a switch to check if PREFLOPBET or not,
                    // (if not preflopbet, then betting starts at 1st index)
                // based on the game rank, will need to create another function to
                    // bluff based on random chance; if higher rank, bluffs more often
                    // or makes less mistakes - always sees optimal hands
                // if player isn't current user, then display e.g. "Deciding..." next
                    // to their name in the UI player list and execute a timer
                    // then update their action, their bet amout, pot total... in the UI
                // if player is current user, then execute while loop below
                while(inGameState == Enums::PREFLOPBET) {
                    Draw::inGame(
                        inGamePlayers,
                        inGamePlayers[0].name,
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
                while (1);
                break;
            }
            case Enums::CALL: {
                cout << "CALL Not Implemented" << '\n';
                while (1);
                break;
            }
            case Enums::RAISE: {
                cout << "RAISE Not Implemented" << '\n';
                while (1);
                break;
            }
            case Enums::BET: {
                cout << "BET Not Implemented" << '\n';
                while (1);
                break;
            }
            case Enums::CHECK: {
                cout << "CHECK Not Implemented" << '\n';
                while (1);
                break;
            }
        }
    }
}