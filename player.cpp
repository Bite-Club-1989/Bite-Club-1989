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
    // mPlayer.setRadius(20);
    // mPlayer.setOrigin(20, 20);
    // mPlayer.setFillColor(sf::Color::Green);
    // mPlayer.setPosition(400, 400);

    mTexture.loadFromFile("assets/textures/Bodyedit.png");
    mSprite.setTexture(mTexture);
    // mSprite.setTextureRect(sf::IntRect(40, 40, 40, 40));
    mSprite.setPosition(400, 400);
    mSprite.setOrigin(20, 20);

    mState = PlayerState::Alive;
    mAction = PlayerAction::Idle;

    mXP = 0;            // experience points
    mHP = 50;           // hit points
    mHealth = 100;      // health
    mLevel = 1;         // level
    mScore = 0;         // score
    mPlayerSpeed = 100; // player speed
    mBulletSpeed = 750; // bullet speed
}

// Move the player
void Player::playerMove(float dt)
{
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && mPlayer.getPosition().y > 0)
    //     mPlayer.move(0, -mPlayerSpeed * dt); // move up

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && mPlayer.getPosition().y < 800)
    //     mPlayer.move(0, mPlayerSpeed * dt); // move down

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && mPlayer.getPosition().x > 0)
    //     mPlayer.move(-mPlayerSpeed * dt, 0); // move left

    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && mPlayer.getPosition().x < 800)
    //     mPlayer.move(mPlayerSpeed * dt, 0); // move right

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && mSprite.getPosition().y > 0)
        mSprite.move(0, -mPlayerSpeed * dt); // move up

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && mSprite.getPosition().y < 800)
        mSprite.move(0, mPlayerSpeed * dt); // move down

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && mSprite.getPosition().x > 0)
        mSprite.move(-mPlayerSpeed * dt, 0); // move left

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && mSprite.getPosition().x < 800)
        mSprite.move(mPlayerSpeed * dt, 0); // move right
}

void Player::playerDeath(sf::RenderWindow &window)
{
    // Player dies
    mPlayer.setFillColor(sf::Color::Red);
    mPlayer.setPosition(400, 400);

    mSprite.setTextureRect(sf::IntRect(0, 40, 40, 40));
    mSprite.setPosition(400, 400);
    mSprite.setRotation(90);
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

void Player::playerWin(sf::RenderWindow &window)
{
}

void Player::playerAttack(sf::RenderWindow &window)
{

    mBullets.push_back(sf::CircleShape(2));
    mBullets.back().setFillColor(sf::Color::White);
    mBullets.back().setOrigin(5, 5);
    mBullets.back().setPosition(mSprite.getPosition());
    mAngles.push_back(atan2(sf::Mouse::getPosition(window).y - mSprite.getPosition().y,
                            sf::Mouse::getPosition(window).x - mSprite.getPosition().x));
}

// Draw the player
void Player::draw(sf::RenderWindow &window, float dt)
{
    playerMove(dt);
    window.draw(mSprite);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mState == PlayerState::Alive)
    {
        mAction = PlayerAction::Attack;
        playerAttack(window);
    }
    else
        mAction = PlayerAction::Idle;

    for (int i = 0; i < mBullets.size(); i++)
    {
        window.draw(mBullets[i]);
        mBullets[i].move(cos(mAngles[i]) * mBulletSpeed * dt, sin(mAngles[i]) * mBulletSpeed * dt);
    }

    if (mState == PlayerState::Dead)
    {
        playerDeath(window);
        playerLose(window);
    }
}
