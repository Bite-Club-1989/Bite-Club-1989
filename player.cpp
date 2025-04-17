/**
 * @file player.cpp
 * @author Chris Bailey (cbailey@nic.edu)
 * @brief The implementation of the player class
 * @version 0.1
 * @date 2025-03-24
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "player.hpp"
#include "weapon.h"
#include "enemy.hpp"

/**
 * @brief Construct a new Player:: Player object
 *         creates instance of weapon object,
 *          passes texture to entity constructor
 *
 */
Player::Player() : Entity("assets/textures/Bodyedit.png"), weapon("gun", 2, 1, 750, true)
{
    // Set the texture rectangle
    mSprite.setTextureRect(sf::IntRect(10, 0, 11, 20)); // Set the texture rectangle (int rectLeft, int rectTop, int rectWidth, int rectHeight)
    mSprite.setTexture(mTexture);                       // Set the texture
    mSprite.setPosition(400, 400);                      // Set the position inside the window
};

/**
 * @brief Destroy the Player:: Player object
 *
 */
Player::~Player() {};

/**
 * @brief This function is used to move the player
 *
 * @param dt The delta time between frames (originating from main.cpp)
 */
void Player::playerMove(float dt)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && mSprite.getPosition().y > 0)
        mSprite.move(0, -mSpeed * dt); // move up

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && mSprite.getPosition().y < 800)
        mSprite.move(0, mSpeed * dt); // move down

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && mSprite.getPosition().x > 0)
        mSprite.move(-mSpeed * dt, 0); // move left

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && mSprite.getPosition().x < 800)
        mSprite.move(mSpeed * dt, 0); // move right
}

/**
 * @brief This function is used to attack
 *
 * @param window The window to draw to (originating from game.cpp)
 */
void Player::playerAttack(sf::RenderWindow &window)
{
}

/**
 * @brief This function is used to handle player death
 *
 * @param window The window to draw to (originating from game.cpp)
 */
void Player::playerDeath(sf::RenderWindow &window)
{
    mSprite.setTextureRect(sf::IntRect(0, 0, 35, 35));
    mSprite.setColor(sf::Color::Red);
    mSprite.setRotation(90);
    mSprite.move(0, 0);
    window.draw(mSprite);
}

/**
 * @brief This function is used to draw the player
 *
 * @param window The window to draw to (originating from game.cpp)
 * @param dt The delta time between frames (originating from main.cpp)
 */
void Player::draw(sf::RenderWindow &window, float dt, std::vector<sf::CircleShape> &mBullets)
{
    playerMove(dt);
    window.draw(mSprite);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mState == EntityState::Alive)
    {
        mAction = EntityAction::Attack;
        weapon.attack(window, mSprite, mBullets);
    }
    else
        mAction = EntityAction::Idle;

    weapon.attackRender(window, dt, mBullets);

    if (mState == EntityState::Dead)
    {
        playerDeath(window);
    }
}