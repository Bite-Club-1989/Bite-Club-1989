#include "game.h"
#include "player.hpp"

Game::Game() : mWindow(sf::VideoMode(800, 800), "Bite Club 1989")
{
    mIsDone = false;
    Player player1;
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

void Game::render()
{
    mWindow.clear(sf::Color::Black);
    player1.draw(mWindow);
    mWindow.display();
}

bool Game::isDone() const
{
    return (!mWindow.isOpen() || mIsDone);
}
