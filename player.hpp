/**
 * @file player2.hpp
 * @author your name (you@domain.com)
 * @brief
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
    Player() : Entity("assets/textures/Bodyedit.png")
    {
        mSprite.setPosition(400, 400);
        mBulletSpeed = 750; // bullet speed
    };
    ~Player() {};

    void playerMove(float dt);                                     // Move the player
    void playerAttack(sf::RenderWindow &window);                   // Player attacks
    void draw(sf::RenderWindow &window, float dt, Weapon &weapon); // Draw the player

private:
    std::vector<sf::CircleShape> mBullets;
    std::vector<float> mAngles;
    double mBulletSpeed; // bullet speed
};

#endif