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

class Enemy : public Entity
{
public:
    Enemy() : mSpeed(100.0f) {} // set speed just for testing
    ~Enemy() {}

    // Deals damage to the player if their sprites intersect
    void enemyDealDamage(Player &p)
    {
        if (p.mSprite.getGlobalBounds().intersects(mSprite.getGlobalBounds()) && mState == EntityState::Alive)
        {
            std::cout << "Player Hit" << std::endl;
            p.takeDamage(10);
        }
    }

    // Updates enemy movement toward the player using delta time.
    void enemyMove(Player &p, float dt)
    {
        // Get positions
        // Initialize vector 2f with enemy position
        sf::Vector2f enemyPos = mSprite.getPosition();
        // Initialize vector 2f with player position
        sf::Vector2f playerPos = p.mSprite.getPosition();

        // Find direction the enemy should move to intercept the player
        sf::Vector2f direction = playerPos - enemyPos;

        // Normalize the direction vector
        // calculate the length of the vector using Pythag ttheorem
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length != 0)
        {
            // normalize the vector by dividing by length
            // can be adjusted later to vary chase speed and direction
            direction /= length;
        }

        // Move enemy along the normalized direction.
        // multiply to set speed diredtion with frame rate
        mSprite.move(direction * mSpeed * dt);
        // cout to verify movement
        std::cout << "Enemy Position: " << mSprite.getPosition().x << ", " << mSprite.getPosition().y << std::endl;
    }

    // Override the base class draw method.
    // This function must match the signature in Entity.
    /* virtual void draw(sf::RenderWindow &window) override
    {

       std::cout << "updating enemu" <<std:: endl;

       std::cout << "Drawing Enemy" << std::endl;
       window.draw(mSprite);
    } */

    // needed to create new function to be able to pass player object.
    void updateAndDraw(sf::RenderWindow &window, Player &p, float dt)
    {
        if (mState == EntityState::Alive)
        {
            enemyMove(p, dt);     // Update enemy position toward the player.
            window.draw(mSprite); // Draw the enemy.
        }
        else
        {
            enemyDeath(window);
        }
    }
    void enemyDeath(sf::RenderWindow &window)
    {
        mSprite.setTextureRect(sf::IntRect(0, 0, 35, 35));
        mSprite.setColor(sf::Color::Red);
        mSprite.setRotation(90);
        mSprite.move(0, 0);
        window.draw(mSprite);
        mState = EntityState::Dead;
    }

private:
    float mSpeed; // Enemy movement speed.
};

#endif
