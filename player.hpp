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
    void playerMove(float dt);                     // Move the player
    void playerAttack(sf::RenderWindow &window);   // Player attacks
    void playerDeath(sf::RenderWindow &window);    // Player death
    void draw(sf::RenderWindow &window, float dt); // Draw the player
    void setWpnDmg(float d) { weapon.setWepDmg(d); };

    Weapon &getWeapon() { return weapon; };
    float getStamina() const {return mStamina;}; // get stamina to update hud


private:
    Weapon weapon;                    // Weapon object
    float mStamina = 100.f;           // current stamina value
    float mMaxStamina = 100.f;        // max stamina
    float mStaminaDrainRate = 40.f;   //how much stamina drains per when sprinting
    float mStaminaRecoverRate = 20.f; // how much stamina recovers when not sprinting
};

#endif