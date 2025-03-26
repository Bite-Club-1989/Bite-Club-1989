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
Weapon::Weapon(std::string name, float d, float r, float b, bool ranged)
{
    mName = name;
    mWepDmg = d;
    mRate = r;
    mBulletSpeed = b;
    mRanged = ranged;
}

void Weapon::setWeapon(std::string name, float d, float r, float b, bool ranged)
{
    mName = name;
    mWepDmg = d;
    mRate = r;
    mBulletSpeed = b;
    mRanged = ranged;
}

void Weapon::attack(sf::RenderWindow &window, sf::Sprite &sprite)
{
    if (mFireClock.getElapsedTime().asSeconds() >= mRate)
    {
        mBullets.push_back(sf::CircleShape(2));
        mBullets.back().setFillColor(sf::Color::White);
        mBullets.back().setOrigin(-13, -10);
        mBullets.back().setPosition(sprite.getPosition());
        mAngles.push_back(atan2(sf::Mouse::getPosition(window).y - sprite.getPosition().y,
                                sf::Mouse::getPosition(window).x - sprite.getPosition().x));

        mFireClock.restart();
    }
}

void Weapon::attackRender(sf::RenderWindow &window, float dt)
{
    for (int i = 0; i < mBullets.size(); i++)
    {
        window.draw(mBullets[i]);
        mBullets[i].move(cos(mAngles[i]) * mBulletSpeed * dt, sin(mAngles[i]) * mBulletSpeed * dt);
    }
}

