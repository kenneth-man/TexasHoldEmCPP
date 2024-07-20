#include "screens.h"

string Screens::infoScreen(
    string description,
    string hint
) {
    Draw::title();
    Draw::text(description);
    Draw::text("(" + hint + ")");
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
    const stateMap &stateMap,
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
    Enums::GameState &gameState,
    Enums::Rank gameRank
) {
    bool exit = false;
    cards poolCards;
    cards playerCards;
    Enums::InGameState inGameState = Enums::SMALLBLINDBET;

    while(!exit) {
        Draw::title();

        switch(inGameState) {
            case Enums::SMALLBLINDBET: {
                cout << "SMALLBLINDBET Not Implemented" << '\n';
                while(1);
                break;
            }
            case Enums::BIGBLINDBET: {
                cout << "BIGBLINDBET Not Implemented" << '\n';
                while (1);
                break;
            }
            case Enums::DEALING: {
                cout << "DEALING Not Implemented" << '\n';
                Draw::playingCards(
                    {},
                    {}
                );
                while (1);
                break;
            }
            case Enums::PREFLOPBET: {
                cout << "PREFLOPBET Not Implemented" << '\n';
                while (1);
                break;
            }
            case Enums::FLOP: {
                cout << "FLOP Not Implemented" << '\n';
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
            }
        }
    }
}