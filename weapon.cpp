#include "weapon.h"
/**
 * @file weapon.cpp
 * @author Joe Davitt (jjdavitt@nic.edu)
 * @brief
 * @version 0.1
 * @date 2025-03-23
 *
 * @copyright Copyright (c) 2025
 *
 */

/**
 * @brief Construct a new Weapon:: Weapon object. This constructor will require the following variables passed to it.
 *
 * @param name name of the weapon
 * @param d damage
 * @param r fire rate / speed
 * @param b bullet projectile speed
 * @param ranged boolean flag for ranged weapon
 */
Weapon::Weapon(std::string name, float d, float r, float b, bool ranged)
{
    mName = name;
    mWepDmg = d;
    mRate = r;
    mBulletSpeed = b;
    mRanged = ranged;
}

/**
 * @brief sets the weapon to different variables. ex: changing weapon properties after picking up a new weapon.
 *
 * @param name name of the weapon
 * @param d damage
 * @param r fire rate / speed
 * @param b bullet projectile speed
 * @param ranged boolean for ranged weapon
 */
void Weapon::setWeapon(std::string name, float d, float r, float b, bool ranged)
{
    mName = name;
    mWepDmg = d;
    mRate = r;
    mBulletSpeed = b;
    mRanged = ranged;
}

/**
 * @brief Weapon attack function. Handles both ranged and melee based on the value in mRanged.
 *
 * @param window This is the game window passed in from the Game class (render function).
 * @param sprite This is the player sprite passed in from the Player class (draw function).
 */
void Weapon::attack(sf::RenderWindow &window, sf::Sprite &sprite, std::vector<sf::CircleShape> &mBullets)
{
    if (mRanged) // if a ranged weapon
    {
        if (mFireClock.getElapsedTime().asSeconds() >= mRate) // checks if time since last attack is greater than the weapon rate
        {
            mBullets.push_back(sf::CircleShape(2));
            mBullets.back().setFillColor(sf::Color::White);
            mBullets.back().setOrigin(-13, -10);
            mBullets.back().setPosition(sprite.getPosition()); // sets the bullet starting position to the player sprite
            mAngles.push_back(atan2(sf::Mouse::getPosition(window).y - sprite.getPosition().y,
                                    sf::Mouse::getPosition(window).x - sprite.getPosition().x));

            mFireClock.restart(); //restarts the fire rate clock
        }
    }
    else
    {
        // melee attack will go here
    }
}

/**
 * @brief renders the appropriate attack to the screen
 * 
 * @param window This is the game window passed in from the Game class (render function).
 * @param dt the clock that is passed from the Game class (render function).
 */
void Weapon::attackRender(sf::RenderWindow &window, float dt, std::vector<sf::CircleShape> &mBullets)
{
    if (mRanged)
    {
        for (int i = 0; i < mBullets.size(); i++)
        {
            window.draw(mBullets[i]);
            mBullets[i].move(cos(mAngles[i]) * mBulletSpeed * dt, sin(mAngles[i]) * mBulletSpeed * dt);
        }
    }
    else
    {
        // melee attack render will go here.
    }
}
