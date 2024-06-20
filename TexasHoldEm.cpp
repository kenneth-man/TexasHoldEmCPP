#include <vector>
#include <iostream>
#include "./TexasHoldEm/src/constants/macros.h"
#include "./TexasHoldEm/src/game/draw/draw.h"
#include "./TexasHoldEm/src/constants/variables.h"
#include "./TexasHoldEm/src/constants/typeAliases.h"
#include "./TexasHoldEm/src/game/calc/calc.h"

int main() {
    const vector<menuItem> menuItems = Calc::menuItems(
        Variables::titleScreenActions,
        Variables::xSize,
        Variables::ySize
    );
    menuItem selectedMenuItem = menuItems[0];

    while(1) {
        Draw::title();
        Draw::menu(
            menuItems,
            selectedMenuItem,
            Variables::xSize,
            Variables::ySize
        );
        const char selected = Calc::menuAction(
            menuItems,
            selectedMenuItem
        );
        if (selected != Variables::falsy) {
            //update game state to whatever was selected
        }
    }
}
