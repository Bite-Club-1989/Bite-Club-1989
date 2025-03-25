/**
 * @file entity.hpp
 * @author your name (you@domain.com)
 * @brief
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
        mSprite.setTextureRect(sf::IntRect(35, 0, 35, 35));
        mSprite.setTexture(mTexture);
        mSprite.setPosition(200, 400);
        mSprite.setOrigin(20, 20);

        mXP = 0;
        mHP = 50;
        mHealth = 100;
        mSpeed = 100;

        mState = EntityState::Alive;
        mAction = EntityAction::Idle;
    };
    Entity(const std::string &texture)
    {
        mTexture.loadFromFile(texture);
        mSprite.setTexture(mTexture);

        mXP = 0;
        mHP = 50;
        mHealth = 100;
        mSpeed = 100;

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