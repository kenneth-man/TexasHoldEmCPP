#include "screens.h"

char Screens::infoScreen(
    const string description,
    const string hint
) {
    Draw::title();
    Draw::text(description);
    Draw::text("(" + hint + ")");
    return _getch();
}

void Screens::errorScreen(const string description) {
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