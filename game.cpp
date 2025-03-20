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
    mWindow.display();
}

bool Game::isDone() const
{
    return (!mWindow.isOpen() || mIsDone);
}
