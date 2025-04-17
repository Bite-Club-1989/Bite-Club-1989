/**
 * @file weapon.h
 * @author Joe Davitt (jjdavitt@nic.edu)
 * @brief
 * @version 0.1
 * @date 2025-03-23
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef WEAPON_H
#define WEAPON_H

#include <SFML/Graphics.hpp>
#include "timer.hpp"

class Weapon
{
public:
    Weapon(std::string name, float d, float r, float b, bool ranged);
    ~Weapon() {}

    void setRate(float r) { mRate = r; }
    void setWepDmg(float d) { mWepDmg = d; }
    void setWeapon(std::string name, float d, float r, float b, bool ranged);

    void attack(sf::RenderWindow &window, sf::Sprite &sprite);
    void attackRender(sf::RenderWindow &window, float dt);

    float getRate() { return mRate; }
    float getWepDmg() { return mWepDmg; }
    std::string getWepName() { return mName; }

    std::vector<float> mAngles;

    struct Projectile
    {
        sf::CircleShape bullet;
        float angle;

        Projectile(const sf::Vector2f &pos, float ang) : angle(ang)
        {
            bullet.setRadius(2);
            bullet.setFillColor(sf::Color::White);
            bullet.setOrigin(-13, -10);
            bullet.setPosition(pos);
        }
    };

    std::vector<Weapon::Projectile> mProjectiles;

    std::vector<Weapon::Projectile> &getProjectiles()
    {
        return mProjectiles;
    }

    double getBulletSpeed()
    {
        return mBulletSpeed;
    };

    protected:
    sf::Texture mTexture;
    // sf::Sprite mSprite; // this is commented out for now until in use
    sf::Clock mFireClock;
    // std::vector<sf::CircleShape> mBullets; // this stores the bullets in a vector to be drawn to screen
    double mBulletSpeed; // bullet speed
    bool mRanged;        // flag that will be used for ranged attacks

    std::string mName;
    int mID;
    float mWepDmg, mRate;
};

#endif