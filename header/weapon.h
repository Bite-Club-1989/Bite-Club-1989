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


    Weapon(std::string name, float d, float r, float b, bool ranged); // Constructor
    ~Weapon() {}                                                      // Destructor

    void setRate(float r) { mRate = r; }                                      // Set rate of fire
    void setWepDmg(float d) { mWepDmg = d; }                                  // Set weapon damage
    void setWeapon(std::string name, float d, float r, float b, bool ranged); // Set weapon properties

    void attack(sf::RenderWindow &window, sf::Sprite &sprite); // Attack function
    void attackRender(sf::RenderWindow &window, float dt);     // Render attack
    void loadSoundBuffer(WpnSoundState w);                     // Load sound buffer

    void setBulletsFired(int i) { mBulletsFired = i; } // Set bullets fired

    float getRate() { return mRate; }          // Get rate of fire
    float getWepDmg() { return mWepDmg; }      // Get weapon damage
    std::string getWepName() { return mName; } // Get weapon name

    std::vector<float> mAngles; // Vector of angles for bullets



    /**
     * @brief weapon projectile class that will be used for the bullets
     *
     */
    struct Projectile
    {
        /**
         * @brief Construct a new Projectile object
         *
         * @param pos The position of the projectile
         * @param ang The angle of the projectile
         */
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

        sf::CircleShape bullet; // Bullet shape
        float angle;            // Angle of the bullet
        BulletState mState;     // State of the bullet
    };

    std::vector<Weapon::Projectile> mProjectiles; // Vector of projectiles


    int mBulletsFired; // Number of bullets fired

    /**
     * @brief Get the Bullet Speed object
     *
     * @return double The bullet speed
     */

    double getBulletSpeed()
    {
        return mBulletSpeed;
    };

    WpnSoundState mBulletSound; // Bullet sound state

protected:

    sf::Texture mTexture;             // Texture for the weapon
    sf::Clock mFireClock;             // Clock for firing
    std::vector<sf::Sound> mGunshots; // Vector of gunshot sounds
    sf::SoundBuffer mGunshotBuffer;   // Sound buffer for gunshot sounds
    double mBulletSpeed;              // bullet speed
    bool mRanged;                     // flag that will be used for ranged attacks

    std::string mName;              // Name of the weapon
    int mID;                        // ID of the weapon
    float mWepDmg, mRate;           // Weapon damage and rate of fire
    std::string mGunshotLocation;   // Gunshot sound location
    std::string mLasershotLocation; // Laser sound location
    int mSoundIndex = 0;            // Index of the current sound

};

#endif