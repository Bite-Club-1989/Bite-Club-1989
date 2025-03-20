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

    mXP = 0;       // experience points
    mHP = 50;      // hit points
    mHealth = 100; // health
    mLevel = 1;    // level
    mScore = 0;    // score
    mSpeed = 0.1;  // speed
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

void Player::playerDeath(sf::RenderWindow &window)
{
    // Player dies
    mPlayer.setFillColor(sf::Color::Red);
    mPlayer.setPosition(400, 400);
}

void Player::playerLose(sf::RenderWindow &window)
{
    // Player loses
    std::string message = "GAME OVER\nYOU SUCK!";
    sf::Font font;
    if (!font.loadFromFile("Meta-Courage-TTF.ttf"))
        std::cout << "No Text\n";

    sf::Text text;
    font.loadFromFile("Meta-Courage-TTF.ttf");
    text.setFont(font);
    text.setPosition(sf::Vector2f(window.getSize().x / 3.5, 70));
    text.setString(message);
    text.setCharacterSize(54);
    text.setFillColor(sf::Color::White);

    window.draw(text);
}

// Draw the player
void Player::draw(sf::RenderWindow &window)
{
    playerMove();
    window.draw(mPlayer);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        // playerAttack();
        mBullets.push_back(sf::CircleShape(5));
        mBullets.back().setFillColor(sf::Color::Yellow);
        mBullets.back().setOrigin(5, 5);
        mBullets.back().setPosition(mPlayer.getPosition());
        angles.push_back(atan2(sf::Mouse::getPosition(window).y - mPlayer.getPosition().y,
                               sf::Mouse::getPosition(window).x - mPlayer.getPosition().x));
    }

    for (int i = 0; i < mBullets.size(); i++)
    {
        window.draw(mBullets[i]);
        mBullets[i].move(cos(angles[i]) * 0.75, sin(angles[i]) * 0.75);
    }

    // if (mHealth <= 0)
    // {
    //     mState = PlayerState::Dead;
    // }

    if (mState == PlayerState::Dead)
    {
        playerDeath(window);
        playerLose(window);
    }
}