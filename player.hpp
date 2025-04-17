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
    void playerMove(float dt);                                                             // Move the player
    void playerAttack(sf::RenderWindow &window);                                           // Player attacks
    void playerDeath(sf::RenderWindow &window);                                            // Player death
    void draw(sf::RenderWindow &window, float dt, std::vector<sf::CircleShape> &mBullets); // Draw the player
    void setWpnDmg(float d) { weapon.setWepDmg(d); };

private:
    Weapon weapon; // Weapon object
};

#endif