/**
 * @file entity.hpp
 * @author Chris Bailey (cbailey@nic.edu)
 * @brief The entity class that will be the base class for all character type classes
 * @version 0.1
 * @date 2025-03-24
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <iostream>
#include <SFML/Graphics.hpp>

class Entity
{
public:
    Entity();                           // Default constructor, enemy will use this
    Entity(const std::string &texture); // Constructor with texture, player will use this
    ~Entity();                          // Destructor that does nothing

    enum class EntityState // States that the entity can be in
    {
        Alive, // Default state
        Dead   // Dead state
    };

    enum class EntityAction // Actions that the entity can take
    {
        Idle,   // Entity Default action non-moving
        Moving, // Entity is moving
        Attack, // Entity is executing attack
        Defend, // Entity is executing defend
        Hurt,   // Entity is hurt
    };

    // Functions that can be used or overided by derived classes
    virtual void experience(int xp);                // Experience points used for leveling up
    virtual void hitPoints(int hp);                 // Hit points used for damage calculations
    virtual void health(int health);                // Health points used for health bar
    virtual void speed(float speed);                // Speed of the entity
    virtual void position(sf::Vector2f position);   // Position of the entity
    virtual void draw(sf::RenderWindow &window);    // Draw the entity
    virtual void takeDamage(int amount);            // Take damage from an attack
    virtual void setTexture(sf::Texture texture);   // Set the texture of the entity
    virtual void setSprite(sf::Sprite sprite);      // Set the sprite of the entity
    virtual void changeState(EntityState state);    // Change the state of the entity
    virtual void changeAction(EntityAction action); // Change the action of the entity

    // Variables
    int mXP;      // Member variable for experience points
    int mHP;      // Member variable for hit points
    int mHealth;  // Member variable for health points
    float mSpeed; // Member variable for speed

    // Shape and texture
    sf::CircleShape mEnemy;
    sf::Texture mTexture; // Member variable for the texture
    sf::Sprite mSprite;   // Member variable for the sprite

    // State and action
    EntityState mState;   // Member variable for the state
    EntityAction mAction; // Member variable for the action
};

#endif