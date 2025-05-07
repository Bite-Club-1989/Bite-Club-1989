/**
 * @file main.cpp
 * @author Chris Joe and Tyler
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
  sf::Clock gameClock; //initialize game clock
  Game game; //initialize game object
  game.playSplash(); //play splash screen
  game.resetGame(); // upon starting game (enter) reset all variables
  gameClock.restart(); //restart the clock
  while (1)
  {
    while (!game.isDone()) 
    {
      game.handleInput();
      float dt = gameClock.restart().asSeconds();
      game.update(dt);
      game.render();
      
      
    }
    game.playEnd(); //end splash screen
    game.resetGame(); //reset the game after enter is pressed 
    gameClock.restart(); // restart the clock
  }

  return 0;
}