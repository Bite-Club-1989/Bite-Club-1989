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

    void attack(sf::RenderWindow &window, sf::Sprite &sprite);
    void attackRender(sf::RenderWindow &window, float dt);

    float getRate() { return mRate; }
    float getWepDmg() { return mWepDmg; }
    std::string getWepName() { return mName; }

protected:
    sf::Texture mTexture;
    // sf::Sprite mSprite;
    sf::Clock mFireClock;
    std::vector<sf::CircleShape> mBullets;
    std::vector<float> mAngles;
    double mBulletSpeed; // bullet speed
    bool mRanged;

    std::string mName;
    int mID;
    float mWepDmg, mRate;
};



#endif