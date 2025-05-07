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
#include "../header/player.hpp"
#include "../header/weapon.h"
#include "../header/enemy.hpp"

/**
 * @brief Construct a new Player:: Player object
 *         creates instance of weapon object,
 *          passes texture to entity constructor
 *
 */
Player::Player() : Entity("../assets/textures/Bodyedit.png"), weapon("gun", 0.25, 0.25, 750, true)
{
    // Set the texture rectangle
    mSprite.setTextureRect(sf::IntRect(10, 0, 11, 20)); // Set the texture rectangle (int rectLeft, int rectTop, int rectWidth, int rectHeight)
    mSprite.setTexture(mTexture);                       // Set the texture
    auto bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f); // Set the origin to the center of the sprite
    mSprite.setPosition(400, 400);                              // Set the position inside the window
    mSpeed *= 1.2f;                                             // Set the speed of the player

    setWpnDmg(30);

    mSoundIndex = 0;

    if (!mDamageBuffer.loadFromFile("../assets/sounds/impact.ogg"))
    {
        std::cerr << "Failed to load gunshot\n";
    }
    else
    {
        mDamageSounds.resize(5);
        for (int i = 0; i < 5; i++)
        {
            mDamageSounds[i].setBuffer(mDamageBuffer);
        }
    }
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && mSprite.getPosition().y > 30)
        {
            dir.y -= 1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && mSprite.getPosition().y < 920)
        {
            dir.y += 1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && mSprite.getPosition().x > 35)
        {
            dir.x -= 1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && mSprite.getPosition().x < 1140)
        {

            dir.x += 1.f;
        }
        // If player is fatigued, apply penalty
        if (mIsFatigued)
        {
            mFatigueTimer += dt;                   // penalty timer
            if (mFatigueTimer >= mFatigueDuration) // penalty is over
            {

                mIsFatigued = false; // penalty is over reset fatigue
                mFatigueTimer = 0.f; // reset timer
            }
        }
        // allow sprinting if player is not fatigued
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
                {
                    mStamina = mMaxStamina;
                }
                mSpeedboost = 1.0f;
            }
        }
        // std::cout << "Stamina: " << mStamina << std::endl;
        // use this function to move the player in the desired direction with consistent speed
        if (dir.x != 0.f || dir.y != 0.f)
        {
            // use pythag theorem to find length like the enemy
            float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            dir /= length; // level the vector to 1 for even movement

            // move based on gamespeed * setspeed (mSpped) * speedboost condition
            dir *= mSpeed * dt * mSpeedboost;
            // flip sprite flag based on direction
            mSprite.move(dir);
            if (dir.x < 0)
            {
                setFacingRight(false);
            }
            else if (dir.x > 0)
            {
                setFacingRight(true);
            }
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
    // mSprite.setTextureRect(sf::IntRect(0, 0, 35, 35));
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
    // allow attack if alive
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    {
        if (mWpnChangeClock.getElapsedTime().asSeconds() >= 0.5)
        {
            if (weapon.mBulletSound == Weapon::WpnSoundState::Laser)
            {
                weapon.loadSoundBuffer(Weapon::WpnSoundState::Gun);
            }
            else
            {
                weapon.loadSoundBuffer(Weapon::WpnSoundState::Laser);
            }
            mWpnChangeClock.restart();
        }
    }
}

/**
 * @brief This function is used to take damage from an attack
 *
 * @param amount The amount of damage to take
 */
void Player::takeDamage(int amount)
{
    mHealth -= amount;
    if (mHealth <= 0)
        mState = EntityState::Dead;

    // Damage sound play
    if (mSoundIndex >= 0 && mSoundIndex < mDamageSounds.size())
    {
        mDamageSounds[mSoundIndex].stop();
        mDamageSounds[mSoundIndex].play();
        mSoundIndex = (mSoundIndex + 1) % mDamageSounds.size();
    }
}

void Player::changeState(EntityState state)
{
    mState = state;
    if (state == Entity::EntityState::Alive)
    {
        mSprite.setColor(sf::Color::White);
        mSprite.setRotation(0);
    }
}