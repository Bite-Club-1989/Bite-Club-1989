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
    mSpeed *= 1.2f;                                     // Set the speed of the player

    setWpnDmg(30);
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
    if (mState == EntityState::Alive)
    {
        // initialize speedboost with shift key
        float mBoostSpeed = 1.0f;
        // initialize vector 2f for movement
        sf::Vector2f dir(0.f, 0.f);
        // will take keyboard input to determine direction of player
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && mSprite.getPosition().y > 0)
            dir.y -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && mSprite.getPosition().y < 800)
            dir.y += 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && mSprite.getPosition().x > 0)
            dir.x -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && mSprite.getPosition().x < 800)
            dir.x += 1.f;
        if (mIsFatigued)
        {
            mFatigueTimer += dt;                   // penalty timer
            if (mFatigueTimer >= mFatigueDuration) // penalty is over
            {

                mIsFatigued = false; // penalty is over reset fatigue
                mFatigueTimer = 0.f; // reset timer
            }
        }
        else
        {
            // If not fatigued, allow sprinting
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && mStamina > 0.f)
            {
                mSpeedboost = 1.4f;
                mStamina -= mStaminaDrainRate * dt;

                if (mStamina <= 0.f)
                {
                    mStamina = 0.f;
                    mIsFatigued = true; // PLAYER BECOMES FATIGUED
                    mFatigueTimer = 0.f;
                }
            }
            else
            {
                // Recover stamina if NOT holding Shift
                mStamina += mStaminaRecoverRate * dt;
                if (mStamina > mMaxStamina)
                    mStamina = mMaxStamina;
            }
        }
        std::cout << "Stamina: " << mStamina << std::endl;
        // use this function to move the player in the desired direction with consistent speed
        if (dir.x != 0.f || dir.y != 0.f)
        {
            // use pythag theorem to find length like the enemy
            float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            dir /= length; // level the vector to 1 for even movement

            // move based on gamespeed * setspeed (mSpped) * speedboost condition
            dir *= mSpeed * dt * mSpeedboost;

            mSprite.move(dir);
        }
    }
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