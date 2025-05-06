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
#include "../header/game.h"
#include "../header/player.hpp"
#include "../header/weapon.h"
#include "../header/splashscreens.h"

int main()
{
  sf::Clock gameClock;
  Game game;
  game.playSplash();
  while (1)
  {
    while (!game.isDone())
    {
      game.handleInput();
      float dt = gameClock.restart().asSeconds();
      game.update(dt);
      game.render();
      if(game.isDone()){
        game.playEnd();
      }
    }
    game.resetGame();
  }

  return 0;
}