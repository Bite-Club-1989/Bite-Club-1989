#include <SFML/Graphics.hpp>
#include "game.h"

int main()
{

    Game game;
    while (!game.isDone())
    {
        game.handleInput();
        game.render();
    }

    return 0;
}