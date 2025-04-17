#include "game.h"
#include "player.hpp"
#include "weapon.h"
#include "timer.hpp"
#include <ctime>

Game::Game() : mWindow(sf::VideoMode(800, 800), "Bite Club 1989"), player1(), enemy1()
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

void Game::render(Timer &damageTimer)
{
    mWindow.clear(sf::Color::Black);
    player1.draw(mWindow, mDT, mBullets);
    // enemy1.draw(mWindow);
    enemy1.updateAndDraw(mWindow, player1, mDT);
    enemy1.enemyDealDamage(player1);

    for (int i = 0; i < mBullets.size(); i++)
    {
        if (enemy1.mSprite.getGlobalBounds().intersects(mBullets[i].getGlobalBounds()))
        {
            // enemy1.enemyDeath(mWindow);
            if(damageTimer.ready()){
                enemy1.takeDamage(30);
            }
            std::cout << "ENEMY HIT!" << std::endl;
        }
    }

    mWindow.display();
}

bool Game::isDone() const
{
    return (!mWindow.isOpen() || mIsDone);
}
