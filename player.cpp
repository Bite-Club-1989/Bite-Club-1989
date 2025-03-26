/**
 * @file player.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-03-24
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "player.hpp"
#include "weapon.h"

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
    mBullets.push_back(sf::CircleShape(2));
    mBullets.back().setFillColor(sf::Color::White);
    mBullets.back().setOrigin(-13, -10);
    mBullets.back().setPosition(mSprite.getPosition());
    mAngles.push_back(atan2(sf::Mouse::getPosition(window).y - mSprite.getPosition().y,
                            sf::Mouse::getPosition(window).x - mSprite.getPosition().x));
}

// Draw the player
void Player::draw(sf::RenderWindow &window, float dt, Weapon &weapon)
{
    playerMove(dt);
    window.draw(mSprite);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mState == EntityState::Alive)
    {
        mAction = EntityAction::Attack;
        // playerAttack(window);
        weapon.attack(window, mSprite);
    }
    else
        mAction = EntityAction::Idle;

    // for (int i = 0; i < mBullets.size(); i++)
    // {
    //     window.draw(mBullets[i]);
    //     mBullets[i].move(cos(mAngles[i]) * mBulletSpeed * dt, sin(mAngles[i]) * mBulletSpeed * dt);
    // }
    weapon.attackRender(window, dt);

    if (mState == EntityState::Dead)
    {
        // playerDeath(window);
        // playerLose(window);
    }
}