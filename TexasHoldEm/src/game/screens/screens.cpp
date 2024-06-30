#include "screens.h"

string Screens::infoScreen(
    string description,
    string hint
) {
    Draw::title();
    Draw::text(description);
    Draw::text("(" + hint + ")");
    string input;
    cin >> input;
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
    const stateMap &stateMap
) {
    Draw::title();
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