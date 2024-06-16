#include "./TexasHoldEm/src/game/state/titleScreen/TitleScreen.h"
#include "./TexasHoldEm/src/game/draw/draw.h"
#include "./TexasHoldEm/src/constants/variables.h"
#include "./TexasHoldEm/src/constants/typeAliases.h"

int main() {
    /*TitleScreen::test();*/

    const menuItem selectedItem = Variables::inGameMenu[0];
    Draw::menu(
        Variables::inGameMenu,
        selectedItem,
        Variables::xSizeGameMenu,
        Variables::ySizeGameMenu
    );
}
