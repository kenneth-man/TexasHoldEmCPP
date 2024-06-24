#include "outGame.h"

void OutGame::auth() {
	
}
void OutGame::title(
    const vector<menuItem> &menuItems,
    menuItem &selectedItem,
    Enums::OutGameState &outGameState
) {
    Draw::title();
    Draw::menu(
        menuItems,
        selectedItem,
        Variables::xSize,
        Variables::ySize
    );
    if (
        Calc::menuAction(
            menuItems,
            selectedItem
        )
    ) {
        auto it = Variables::outGameStateMap.find(selectedItem.first);

        if (it != Variables::outGameStateMap.end()) {
            outGameState = it->second;
            return;
        }

        Draw::errorScreen(
            "`titleScreenActions` doesn't map correctly to `outGameStateMap`"
        );
    }
}