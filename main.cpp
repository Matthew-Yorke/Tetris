//***********************************************************************
//***********************************************************************
//****/---------\**/------\**/---------\**/----\***/-------\**/-----\****
//****|_|-| |-|_|**| |----/**|_|-| |-|_|**|  /\ |**\--| |--/** \ \-\/****
//********| |******|  >**********| |******|  \/ /*****| |*******\ \******
//********| |******| |----\******| |******| |\ \***/--| |--\**/\_\ \*****
//********|_|******\------/******|_|******|_| \_\**\-------/**\_____\****
//***********************************************************************
//***********************************************************************
//Created by Matthew D. Yorke using the Allegro 5 library


#include "Game.h"

int main() {
    Game *game = Game::Instance();

    game->Init();
    game->MainLoop();

    return 0;
}