#include "../header/weapon.h"
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
    mBulletsFired = 0;
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
    mBulletsFired = 0;
}

/**
 * @brief Weapon attack function. Handles both ranged and melee based on the value in mRanged.
 *
 * @param window This is the game window passed in from the Game class (render function).
 * @param sprite This is the player sprite passed in from the Player class (draw function).
 */
void Weapon::attack(sf::RenderWindow &window, sf::Sprite &sprite)
{
    if (mRanged) // if a ranged weapon
    {
        // if (mFireClock.getElapsedTime().asSeconds() >= mRate) // checks if time since last attack is greater than the weapon rate
        if (mFireClock.getElapsedTime().asSeconds() >= mRate) // checks if time since last attack is greater than the weapon rate
        {
            // Get player and mouse positions
            sf::Vector2f playerPosition = sprite.getPosition();

            sf::Vector2i pixelPosition = sf::Mouse::getPosition(window);
            sf::Vector2f mousePosition = window.mapPixelToCoords(pixelPosition);

            // Calculate angle between player and mouse
            float angle = std::atan2(static_cast<float>(mousePosition.y) - playerPosition.y,
                                     static_cast<float>(mousePosition.x) - playerPosition.x);

            // Create a new projectile with that position and angle
            Projectile projectile(playerPosition, angle);

            // Add the projectile to the list
            mProjectiles.push_back(projectile);

            mBulletsFired++;

            if (mBulletsFired >= 30)
                mBulletsFired = 0;

            mFireClock.restart();
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
void Weapon::attackRender(sf::RenderWindow &window, float dt)
{
    if (mRanged)
    {

        for (std::size_t i = 0; i < mProjectiles.size(); ++i)
        {
            Projectile &projectile = mProjectiles[i];
            window.draw(projectile.bullet);

            // Move projectile
            float dx = std::cos(projectile.angle) * mBulletSpeed * dt;
            float dy = std::sin(projectile.angle) * mBulletSpeed * dt;
            projectile.bullet.move(dx, dy);
        }
    }
    else
    {
        // melee attack render will go here.
    }
}
