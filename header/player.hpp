/**
 * @file player.hpp
 * @author Chris Bailey (cbailey@nic.edu)
 * @brief The player class
 * @version 0.1
 * @date 2025-03-24
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "weapon.h"

class Player : public Entity
{
public:
    Player();  // Default constructor
    ~Player(); // Destructor

    // Functions
    void playerMove(float dt);                        // Move the player
    void playerAttack(sf::RenderWindow &window);      // Player attacks
    void playerDeath(sf::RenderWindow &window);       // Player death
    void draw(sf::RenderWindow &window, float dt);    // Draw the player
    void setWpnDmg(float d) { weapon.setWepDmg(d); }; // Set weapon damage
    void takeDamage(int amount);                      // Take damage from an attack
    virtual void changeState(EntityState state);      // Change the state of the player

    Weapon &getWeapon() { return weapon; };        // get weapon to update hud
    float getStamina() const { return mStamina; }; // get stamina to update hud
    void resetStamina() { mStamina = 100.f; }

private:
    Weapon weapon;                    // Weapon object
    float mStamina = 100.f;           // current stamina value
    float mSpeedboost = 1.0f;         // speed boost value
    float mMaxStamina = 100.f;        // max stamina
    float mStaminaDrainRate = 40.f;   // how much stamina drains per when sprinting
    float mStaminaRecoverRate = 20.f; // how much stamina recovers when not sprinting
    bool mIsFatigued = false;         // true if player ised all of boost
    float mFatigueTimer = 0.f;        // tracks tired recovery time
    float mFatigueDuration = 2.f;     // 2 second penalt for going to 0 stamina

    std::vector<sf::Sound> mDamageSounds; // Vector of sound objects
    sf::SoundBuffer mDamageBuffer;        // Sound buffer for damage sounds
    int mSoundIndex;                      // Index of the current sound

    sf::Clock mWpnChangeClock; // Clock for weapon change
};

#endif