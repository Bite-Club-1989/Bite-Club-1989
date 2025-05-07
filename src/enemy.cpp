/**
 * @file enemy.cpp
 * @author Tyler Chris and Joe
 * @brief 
 * @version 0.1
 * @date 05-06-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "../header/enemy.hpp"

// Deals damage to the player if their sprites intersect
/**
 * @brief Deal damage f(x)
 * 
 * @param p player object 
 */
void Enemy::enemyDealDamage(Player &p)
{
    if (p.mState == Entity::EntityState::Dead)
    {
        return;
    }
    if (mDamageClock.getElapsedTime().asSeconds() >= mDamageRate)
    {
        if (p.mSprite.getGlobalBounds().intersects(mSprite.getGlobalBounds()) && mState == EntityState::Alive)
        {
            std::cout << "Player Hit" << std::endl;
            p.takeDamage(10);
        }
        mDamageClock.restart();
    }
}

// Updates enemy movement toward the player using delta time.
/**
 * @brief enemy movement f(x)
 * 
 * @param p player object
 * @param dt game time delta
 */
void Enemy::enemyMove(Player &p, float dt)
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
    if (direction.x < 0) // if enemy is chasing left
    {
        setFacingRight(false); // flip sprite
    }
    else if (direction.x > 0) // if enemy is chasing right
    {

        setFacingRight(true); // normal sprite
    }
    
}



// needed to create new function to be able to pass player object.
void Enemy::updateAndDraw(sf::RenderWindow &window, Player &p, float dt)
{
    if (mState == EntityState::Alive)
    {
        enemyMove(p, dt); // Update enemy position toward the player.
        updateHealthBar();
        window.draw(healthBar);
        window.draw(mSprite); // Draw the enemy.
    }
    else
    {
        enemyDeath(window);
    }
}
/**
 * @brief simple enemy death f(x)
 * 
 * @param window game window
 */
void Enemy::enemyDeath(sf::RenderWindow &window)
{
    mSprite.setTextureRect(sf::IntRect(0, 0, 35, 35));
    mSprite.setColor(sf::Color::Red);
    mSprite.setRotation(90);
    mSprite.move(0, 0);
    window.draw(mSprite);
    mState = EntityState::Dead;
}
