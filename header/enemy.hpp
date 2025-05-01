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
    Enemy() : mSpeed(100.0f)
    {
        mDamageRate = 0.25;

        sf::FloatRect bounds = mSprite.getGlobalBounds();

        // Health Bar
        healthBar.setSize(sf::Vector2f(50, 5));
        healthBar.setPosition(bounds.left - 10 / 1.0f, bounds.top - 10 / 1.0f);
        sf::Color healthBarColor = sf::Color(255, 0, 0);
        healthBar.setFillColor(healthBarColor);
    } // set speed just for testing
    ~Enemy()
    {
    }

    // Deals damage to the player if their sprites intersect
    void enemyDealDamage(Player &p);

    // Updates enemy movement toward the player using delta time.
    void enemyMove(Player &p, float dt);

    // Override the base class draw method.
    // This function must match the signature in Entity.
    /* virtual void draw(sf::RenderWindow &window) override
    {

       std::cout << "updating enemu" <<std:: endl;

       std::cout << "Drawing Enemy" << std::endl;
       window.draw(mSprite);
    } */

    // needed to create new function to be able to pass player object.
    void updateAndDraw(sf::RenderWindow &window, Player &p, float dt);
    void enemyDeath(sf::RenderWindow &window);

    void updateHealthBar()
    {
        sf::FloatRect bounds = mSprite.getGlobalBounds();
        healthBar.setSize(sf::Vector2f(this->mHealth / 2, 5));
        healthBar.setPosition(bounds.left - 10 / 1.0f, bounds.top - 10 / 1.0f);
        sf::Color healthBarColor = sf::Color(255, 0, 0);
        healthBar.setFillColor(healthBarColor);
    }

private:
    sf::RectangleShape healthBar;
    float mSpeed; // Enemy movement speed.
    float mDamageRate;
    sf::Clock mDamageClock;
};

#endif
