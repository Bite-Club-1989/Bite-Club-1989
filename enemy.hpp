/**
 * @file enemy.hpp
 * @author Chris Bailey (cbailey@nic.edu)
 * @brief The enemy class
 * @version 0.1
 * @date 2025-03-24
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "entity.hpp"
#include "player.hpp"

class Enemy : public Entity
{
public:
    Enemy() {};
    ~Enemy() {};

    void enemyDealDamage(Player &p)
    {
        if (p.mSprite.getGlobalBounds().intersects(mSprite.getGlobalBounds()))
        {
            std::cout << "Player Hit" << std::endl;
            p.takeDamage(10);
        }
    }
};

#endif