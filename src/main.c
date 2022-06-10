#include "include/game.h"

int main()
{
    struct game * game = game_create();

    game_run(game);

    return 0;
}