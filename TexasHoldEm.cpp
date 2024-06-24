#include <vector>
#include <iostream>
#include "./TexasHoldEm/src/constants/variables.h"
#include "./TexasHoldEm/src/constants/typeAliases.h"
#include "./TexasHoldEm/src/game/calc/calc.h"
#include "./TexasHoldEm/src/constants/enums.h"
#include "./TexasHoldEm/src/game/outGame/outGame.h"

int main() {
    Enums::OutGameState outGameState = Enums::AUTH;
    const vector<menuItem> menuItems = Calc::menuItems(
        Variables::titleScreenActions,
        Variables::xSize,
        Variables::ySize
    );
    menuItem selectedItem = menuItems[0];

    while(1) {
        switch(outGameState) {
            case Enums::AUTH: {
                break;
            }
            case Enums::TITLE: {
                OutGame::title(
                    menuItems,
                    selectedItem,
                    outGameState
                );
                break;
            }
            case Enums::NEWGAME: {
                break;
            }
            case Enums::CONTINUE: {
                break;
            }
            case Enums::LEADERBOARD: {
                break;
            }
            case Enums::INSTRUCTIONS: {
                break;
            }
            case Enums::OPTIONS: {
                break;
            }
            case Enums::QUIT: {

            }
        }
    }
}
