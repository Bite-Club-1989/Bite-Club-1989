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

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Weapon
{
public:
    Weapon(std::string name, float d, float r);
    ~Weapon() {}

    void setRate(float r) { mRate = r; }
    void setWepDmg(float d) { mWepDmg = d; }

    float getRate() { return mRate; }
    float getWepDmg() { return mWepDmg; }

private:
    sf::Texture mTexture;
    sf::Sprite mSprite;

    std::string mName;
    int mID;
    float mWepDmg, mRate;
};

class Stick : public Weapon
{
public:
    Stick() : Weapon("Stick", 2, 1) {}
};

#endif