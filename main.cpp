#include <SFML/Graphics.hpp>
#include "game.h"
#include "player.hpp"

int main()
{
    sf::Clock clock; // starts the clock
    Game game;
    while (!game.isDone())
    {
        game.handleInput();
        float dt=clock.restart().asSeconds();
        game.update(dt);
        game.render();
    }

    return 0;
}