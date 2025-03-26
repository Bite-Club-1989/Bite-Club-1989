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

// Move the player
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

// Player attacks
void Player::playerAttack(sf::RenderWindow &window)
{
}

void Player::playerDeath(sf::RenderWindow &window)
{
    mSprite.setTextureRect(sf::IntRect(0, 0, 35, 35));
    mSprite.setColor(sf::Color::Red);
    mSprite.setRotation(90);
    mSprite.move(0, 0);
    window.draw(mSprite);
}

// Draw the player
void Player::draw(sf::RenderWindow &window, float dt)
{
    playerMove(dt);
    window.draw(mSprite);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mState == EntityState::Alive)
    {
        mAction = EntityAction::Attack;
        weapon.attack(window, mSprite);
    }
    else
        mAction = EntityAction::Idle;

    weapon.attackRender(window, dt);

    if (mState == EntityState::Dead)
    {
        playerDeath(window);
    }
}