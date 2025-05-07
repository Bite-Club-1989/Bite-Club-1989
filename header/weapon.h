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
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <iostream>
/**
 * @brief Holds the weapon class that will be used for the player and enemies
 *
 */
class Weapon
{
public:
    enum class WpnSoundState
    {
        Gun,
        Laser,
        Plasma
    };

    Weapon(std::string name, float d, float r, float b, bool ranged); // weapon constructor
    ~Weapon() {}

    void setRate(float r) { mRate = r; }                                      // fire rate
    void setWepDmg(float d) { mWepDmg = d; }                                  // weapon damage
    void setWeapon(std::string name, float d, float r, float b, bool ranged); // select weapon (later feature not implemented)

    void attack(sf::RenderWindow &window, sf::Sprite &sprite); // attack function
    void attackRender(sf::RenderWindow &window, float dt);     // render attack
    void loadSoundBuffer(WpnSoundState w);                     // sound loading

    void setBulletsFired(int i) { mBulletsFired = i; } // set bullets fired

    float getRate() { return mRate; }          // fire rate
    float getWepDmg() { return mWepDmg; }      // weapon damage
    std::string getWepName() { return mName; } // weapon name (unused-later feature)

    std::vector<float> mAngles; // determines the angle of the bullets
    /**
     * @brief weapon projectile class that will be used for the bullets
     *
     */
    struct Projectile
    {
        Projectile(const sf::Vector2f &pos, float ang) : angle(ang)
        {
            bullet.setRadius(2);
            bullet.setFillColor(sf::Color::White);
            bullet.setOrigin(-13, -10);
            bullet.setPosition(pos);
            mState = BulletState::Active;
        }

        enum class BulletState
        {
            Active, //while fired
            Disabled // when not fired/hit enemy
        };

        sf::CircleShape bullet;
        float angle;
        BulletState mState;
    };

    std::vector<Weapon::Projectile> mProjectiles;

    int mBulletsFired;

    double getBulletSpeed()
    {
        return mBulletSpeed;
    };

    WpnSoundState mBulletSound;

protected:
    sf::Texture mTexture;
    sf::Clock mFireClock;
    std::vector<sf::Sound> mGunshots;
    sf::SoundBuffer mGunshotBuffer;
    double mBulletSpeed; // bullet speed
    bool mRanged;        // flag that will be used for ranged attacks

    std::string mName;
    int mID;
    float mWepDmg, mRate;
    std::string mGunshotLocation;
    std::string mLasershotLocation;
    int mSoundIndex = 0;
};

#endif