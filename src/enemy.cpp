/**
 * @file enemy.cpp
 * @author Chris, Joe, Tyler
 * @brief This file contains the implementation of the enemy class
 * @version 0.1
 * @date 2025-05-06
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../header/enemy.hpp"

/**
 * @brief Construct a new Enemy object
 *
 */
Enemy::Enemy() : mSpeed(100.0f)
{
    mDamageRate = 0.25;

    sf::FloatRect bounds = mSprite.getGlobalBounds();

    // Health Bar
    healthBar.setSize(sf::Vector2f(50, 5));
    healthBar.setPosition(bounds.left - 10 / 1.0f, bounds.top - 10 / 1.0f);
    sf::Color healthBarColor = sf::Color(255, 0, 0);
    healthBar.setFillColor(healthBarColor);
}

/**
 * @brief This function deals damage to the player if their sprites intersect.
 *
 * @param p The player object to check for collision with.
 */
void Enemy::enemyDealDamage(Player &p)
{
    if (p.mState == Entity::EntityState::Dead)
        return;
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

/**
 * @brief This function updates the enemy movement toward the player using delta time.
 *
 * @param p The player object to chase.
 * @param dt The delta time since the last frame.
 */
void Enemy::enemyMove(Player &p, float dt)
{
    // Get positions
    sf::Vector2f enemyPos = mSprite.getPosition();    // Initialize vector 2f with enemy position
    sf::Vector2f playerPos = p.mSprite.getPosition(); // Initialize vector 2f with player position
    sf::Vector2f direction = playerPos - enemyPos;    // Find direction the enemy should move to intercept the player

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
    if (direction.x < 0)
    {

        setFacingRight(false);
    }
    else if (direction.x > 0)
    {

        setFacingRight(true);
    }
}

/**
 * @brief This function updates the enemy and draws it to the window.
 *
 * @param window The window to draw the enemy on.
 * @param p The player object to chase.
 * @param dt The delta time since the last frame.
 */
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
 * @brief This function handles the enemy's death state and look.
 *
 * @param window The window to draw the enemy on.
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

/**
 * @brief This function is used to update the health bar position and size
 *
 */
void Enemy::updateHealthBar()
{
    sf::FloatRect bounds = mSprite.getGlobalBounds();
    healthBar.setSize(sf::Vector2f(this->mHealth / 2, 5));
    healthBar.setPosition(bounds.left - 10 / 1.0f, bounds.top - 10 / 1.0f);
    sf::Color healthBarColor = sf::Color(255, 0, 0);
    healthBar.setFillColor(healthBarColor);
}