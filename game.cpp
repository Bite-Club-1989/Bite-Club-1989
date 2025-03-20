#include "game.h"

Game::Game() : mWindow(sf::VideoMode(800, 800), "Bite Club 1989")
{
    mIsDone = false;

}

void Game::handleInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            // Close window button clicked.
            mWindow.close();
        }
    }
}

void Game::render()
{
    mWindow.clear(sf::Color::Black);
    mWindow.display();
}

bool Game::isDone() const
{
    return (!mWindow.isOpen() || mIsDone);
}