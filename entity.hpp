/**
 * @file entity.hpp
 * @author Chris Bailey (cbailey@nic.edu)
 * @brief The entity class
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
    Entity()
    {
        mTexture.loadFromFile("assets/textures/ZombieShooter/Sprites/Zombie/Zombie.png");
        sf::IntRect textureRect(42, 10, 13, 20);
        mSprite.setTextureRect(textureRect);
        mSprite.setTexture(mTexture);

        // Positioning and scaling
        mSprite.setPosition(200, 400);
        mSprite.setOrigin(0, 0);
        mSprite.setScale(2, 2);

        // Attributes
        mXP = 0;
        mHP = 50;
        mHealth = 100;
        mSpeed = 90;

        // State and action
        mState = EntityState::Alive;
        mAction = EntityAction::Idle;
    };
    Entity(const std::string &texture)
    {
        mTexture.loadFromFile(texture);

        // Positioning and scaling
        mSprite.setOrigin(0, 0);
        mSprite.setScale(2, 2);

        // Attributes
        mXP = 0;
        mHP = 50;
        mHealth = 100;
        mSpeed = 100;

        // State and action
        mState = EntityState::Alive;
        mAction = EntityAction::Idle;
    };
    ~Entity() {};
    virtual void experience(int xp) { mXP = xp; };
    virtual void hitPoints(int hp) { mHP = hp; };
    virtual void health(int health) { mHealth = health; };
    virtual void speed(float speed) { mSpeed = speed; };
    virtual void position(sf::Vector2f position) { mSprite.setPosition(position); };
    virtual void draw(sf::RenderWindow &window) { window.draw(mSprite); };
    virtual void takeDamage(int amount)
    {
        mHealth -= amount;
        if (mHealth <= 0)
            mState = EntityState::Dead;
    }
    virtual void setTexture(sf::Texture texture)
    {
        mTexture = texture;
        mSprite.setTexture(mTexture);
    };
    virtual void setSprite(sf::Sprite sprite) { mSprite = sprite; };

    enum class EntityState
    {
        Alive,
        Dead
    };

    enum class EntityAction
    {
        Idle,
        Moving,
        Attack,
        Defend,
    };

    int mXP;
    int mHP;
    int mHealth;
    float mSpeed;

    sf::CircleShape mEnemy;
    sf::Texture mTexture;
    sf::Sprite mSprite;

    EntityState mState;
    EntityAction mAction;

    virtual void changeState(EntityState state) { mState = state; };
    virtual void changeAction(EntityAction action) { mAction = action; };
};

#endif