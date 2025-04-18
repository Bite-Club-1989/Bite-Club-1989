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

class Weapon
{
public:
    Weapon(std::string name, float d, float r, float b, bool ranged);
    ~Weapon() {}

    void setRate(float r) { mRate = r; }
    void setWepDmg(float d) { mWepDmg = d; }
    void setWeapon(std::string name, float d, float r, float b, bool ranged);

    void attack(sf::RenderWindow &window, sf::Sprite &sprite, std::vector<sf::CircleShape> &mBullets);
    void attackRender(sf::RenderWindow &window, float dt, std::vector<sf::CircleShape> &mBullets);

    float getRate() { return mRate; }
    float getWepDmg() { return mWepDmg; }
    std::string getWepName() { return mName; }

protected:
    sf::Texture mTexture;
    // sf::Sprite mSprite; // this is commented out for now until in use
    sf::Clock mFireClock;
    // std::vector<sf::CircleShape> mBullets; // this stores the bullets in a vector to be drawn to screen
    std::vector<float> mAngles;
    double mBulletSpeed; // bullet speed
    bool mRanged;        // flag that will be used for ranged attacks

    std::string mName;
    int mID;
    float mWepDmg, mRate;
};

#endif