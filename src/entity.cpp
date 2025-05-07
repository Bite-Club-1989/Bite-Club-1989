/**
 * @file entity.cpp
 * @author Chris Bailey (cbailey@nic.edu)
 * @brief This file contains the implementation of the entity class
 * @version 0.1
 * @date 2025-03-26
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../header/entity.hpp"

/**
 * @brief Construct a new Entity:: Entity object
 *         primarily used for the enemy class
 *
 */
Entity::Entity()
{
    // Texture and sprite
    mTexture.loadFromFile("../assets/textures/ZombieShooter/Sprites/Zombie/Zombie.png"); // Load the texture from file
    sf::IntRect textureRect(42, 10, 13, 20);                                             // Set the texture rectangle (int rectLeft, int rectTop, int rectWidth, int rectHeight)
    mSprite.setTextureRect(textureRect);                                                 // Set the texture rectangle
    mSprite.setTexture(mTexture);                                                        // Set the texture

    // Positioning and scaling
    mSprite.setPosition(200, 400); // Set the position inside the window
    mSprite.setOrigin(0, 0);       // Set the origin of the sprite
    mSprite.setScale(2, 2);        // Set the scale of the sprite based off png size

    // Attributes
    mXP = 0;       // Set the experience points to 0
    mHP = 50;      // Set the hit points to 50
    mHealth = 100; // Set the health points to 100
    mSpeed = 90;   // Set the speed to 90

    // State and action
    mState = EntityState::Alive;  // Set the state to alive
    mAction = EntityAction::Idle; // Set the action to idle
};

/**
 * @brief Construct a new Entity:: Entity object
 *         primarily used for the player class
 *
 * @param texture The texture of the entity
 */
Entity::Entity(const std::string &texture)
{
    // Texture
    mTexture.loadFromFile(texture); // Load from texture argument

    // Positioning and scaling
    mSprite.setOrigin(0, 0); // Set the origin of the sprite
    mSprite.setScale(2, 2);  // Set the scale of the sprite based off png size

    // Attributes
    mXP = 0;       // Set the experience points to 0
    mHP = 50;      // Set the hit points to 50
    mHealth = 100; // Set the health points to 100
    mSpeed = 100;  // Set the speed to 100

    // State and action
    mState = EntityState::Alive;  // Set the state to alive
    mAction = EntityAction::Idle; // Set the action to idle
};

/**
 * @brief Destroy the Entity:: Entity object
 *
 */
Entity::~Entity() {};

/**
 * @brief This function is used to set the member experience points of the entity
 *
 * @param xp The experience points to set
 */
void Entity::experience(int xp) { mXP = xp; };

/**
 * @brief This function is used to set the member hit points of the entity
 *
 * @param hp The hit points to set
 */
void Entity::hitPoints(int hp) { mHP = hp; };

/**
 * @brief This function is used to set the member health points of the entity
 *
 * @param health The health points to set
 */
void Entity::health(int health) { mHealth = health; };

/**
 * @brief This function is used to get the member health points of the entity
 *
 * @return int The health points of the entity
 */
int Entity::getHealth() { return mHealth; };

/**
 * @brief This function is used to set the member speed of the entity
 *
 * @param speed The speed to set
 */
void Entity::speed(float speed) { mSpeed = speed; };

/**
 * @brief This function is used to set the member position of the entity
 *
 * @param position The position to set
 */
void Entity::position(sf::Vector2f position) { mSprite.setPosition(position); };

/**
 * @brief This function is used to draw the entity to the window
 *
 * @param window The window to draw the entity to (originating from game.cpp)
 */
void Entity::draw(sf::RenderWindow &window) { window.draw(mSprite); };

/**
 * @brief This function is used to take damage from an attack
 *
 * @param amount The amount of damage to take
 */
void Entity::takeDamage(int amount)
{
    mHealth -= amount;
    if (mHealth <= 0)
        mState = EntityState::Dead;
}

/**
 * @brief This function is used to set the texture of the entity
 *
 * @param texture The texture to set
 */
void Entity::setTexture(sf::Texture texture)
{
    mTexture = texture;
    mSprite.setTexture(mTexture);
};

/**
 * @brief This function is used to set the sprite of the entity
 *
 * @param sprite The sprite to set
 */
void Entity::setSprite(sf::Sprite sprite) { mSprite = sprite; };

/**
 * @brief This function is used to change the state of the entity
 *
 * @param state The state to change to
 */
void Entity::changeState(EntityState state) { mState = state; };

/**
 * @brief This function is used to change the action of the entity
 *
 * @param action The action to change to
 */
void Entity::changeAction(EntityAction action) { mAction = action; };

/**
 * @brief This function is used to set the facing direction of the entity
 *
 * @param right The direction to face
 */
void Entity::setFacingRight(bool right)
{
    if (right == mFacingRight)
    {
        return;
    }
    mFacingRight = right;
    auto s = mSprite.getScale();
    mSprite.setScale((right ? +1.f : -1.f) * std::abs(s.x), std::abs(s.y));
}

/**
 * @brief This function is used to center the origin of the entity
 *
 */
void Entity::centerOrigin()
{
    auto b = mSprite.getLocalBounds();
    mSprite.setOrigin(b.width / 2.f, b.height / 2.f);
}