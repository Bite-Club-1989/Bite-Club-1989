#include "game.h"
#include "player.hpp"
#include "weapon.h"

Game::Game() : mWindow(sf::VideoMode(800, 800), "Bite Club 1989"), player1(), weapon1("gun", 2, 1, 750), enemy1()
{
    mIsDone = false;
}

void Game::handleInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            mWindow.close();
            break;

        default:
            break;
        }
    }
}

void Game::update(float dt)
{
    mDT = dt;
}

void Game::render()
{
    mWindow.clear(sf::Color::Black);
    player1.draw(mWindow, mDT, weapon1);
    enemy1.draw(mWindow);
    enemy1.enemyDealDamage(player1);
    mWindow.display();
}

bool Game::isDone() const
{
    return (!mWindow.isOpen() || mIsDone);
}
