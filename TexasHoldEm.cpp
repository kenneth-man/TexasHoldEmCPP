#include <vector>
#include <iostream>
#include "./TexasHoldEm/src/constants/macros.h"
#include "./TexasHoldEm/src/game/draw/draw.h"
#include "./TexasHoldEm/src/constants/variables.h"
#include "./TexasHoldEm/src/constants/typeAliases.h"
#include "./TexasHoldEm/src/game/calc/calc.h"

int main() {
    // \x9C = £
    vector<menuItem> menuItems = Calc::menuItems(
        Variables::titleScreenActions,
        Variables::xSize,
        Variables::ySize
    );
    Draw::wideChar(SPADE, true);
    Draw::menu(
        menuItems,
        menuItems[0],
        Variables::xSize,
        Variables::ySize
    );
}
