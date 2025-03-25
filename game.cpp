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

void Game::update(float dt)
{
    mDT = dt;
}

void Game::render()
{
    mWindow.clear(sf::Color::Black);
    // mBackground.loadFromFile("assets/textures/testBackground.png");
    // mSpriteBackground.setTexture(mBackground);
    // mSprite.setTextureRect(sf::IntRect(40, 40, 40, 40));
    // mSpriteBackground.setPosition(400, 400);
    // mSpriteBackground.scale(0.2f, 0.2f);
    // mSpriteBackground.setScale(0.5f, 0.5f);
    // mSpriteBackground.setOrigin(20, 20);
    // mWindow.draw(mSpriteBackground);
    player1.draw(mWindow, mDT);
    enemy1.draw(mWindow);
    mWindow.display();
}

bool Game::isDone() const
{
    return (!mWindow.isOpen() || mIsDone);
}
