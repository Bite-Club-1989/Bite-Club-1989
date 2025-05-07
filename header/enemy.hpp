/**
 * @file enemy.hpp
 * @brief Basic enemy class
 * @author ...
 * @date 2025-04-05
 *
 * This class inherits from Entity and provides enemy-specific behaviors,
 * such as chasing the player and dealing damage.
 */

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "player.hpp"
#include <cmath>
#include <vector>

class Enemy : public Entity
{
public:
    Enemy(); // Constructor

    void enemyDealDamage(Player &p);                                   // Deals damage to the player if their sprites intersect
    void enemyMove(Player &p, float dt);                               // Updates enemy movement toward the player using delta time.
    void updateAndDraw(sf::RenderWindow &window, Player &p, float dt); // Override the base class draw method
    void enemyDeath(sf::RenderWindow &window);                         // Draw the enemy and health bar
    void updateHealthBar();                                            // Update the health bar position and size

private:
    sf::RectangleShape healthBar; // Health bar for the enemy
    float mSpeed;                 // Enemy movement speed.
    float mDamageRate;            // Damage rate for the enemy
    sf::Clock mDamageClock;       // Clock to track damage time
};

#endif
