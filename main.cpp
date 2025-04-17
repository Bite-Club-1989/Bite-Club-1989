/**
 * @file main.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-24
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <SFML/Graphics.hpp>
#include "game.h"
#include "player.hpp"
#include "weapon.h"
#include "timer.hpp"

int main()
{
    Timer damageTimer(0.25f);
    sf::Clock clock; // starts the clock
    Game game;
    while (!game.isDone())
    {
        game.handleInput();
        float dt = clock.restart().asSeconds();
        game.update(dt);
        game.render(damageTimer);
    }

    return 0;
}