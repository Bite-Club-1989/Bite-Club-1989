/**
 * @file player.cpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-20
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "player.hpp"

// Player will be inside of the game window
Player::Player()
{
    mPlayer.setRadius(20);
    mPlayer.setOrigin(20, 20);
    mPlayer.setFillColor(sf::Color::Green);
    mPlayer.setPosition(400, 400);
}

// Move the player
void Player::playerMove()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        mPlayer.move(0, -0.1); // move up

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        mPlayer.move(0, 0.1); // move down

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        mPlayer.move(-0.1, 0); // move left

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        mPlayer.move(0.1, 0); // move right
}

// Draw the player
void Player::draw(sf::RenderWindow &window)
{
    playerMove();
    window.draw(mPlayer);
}