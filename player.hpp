/**
 * @file player.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-03-20
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <SFML/Graphics.hpp>

class Player
{
public:
    Player();
    ~Player() {};

    void playerMove(float);
    void playerDeath(sf::RenderWindow &window);
    void playerLose(sf::RenderWindow &window);
    void playerWin(sf::RenderWindow &window);
    void playerAttack(sf::RenderWindow &window);

    void setPlayerExperience(int xp) { mXP = xp; };
    void setPlayerHitPoints(int hp) { mHP = hp; };
    void setPlayerHealth(int health) { mHealth = health; };
    void setPlayerLevel(int level) { mLevel = level; };
    void setPlayerScore(int score) { mScore = score; };
    void setPlayerSpeed(float speed) { mPlayerSpeed = speed; };
    void setBulletSpeed(float speed) { mBulletSpeed = speed; };

    void draw(sf::RenderWindow &window, float);

    enum class PlayerState
    {
        Alive,
        Dead,
        Win
    };

    enum class PlayerAction
    {
        Idle,
        Attack,
        Defend,
        LevelUp,
    };

private:
    sf::CircleShape mPlayer;
    sf::Texture mTexture;
    sf::Sprite mSprite;
    PlayerState mState;
    PlayerAction mAction;
    std::vector<sf::CircleShape> mBullets;
    std::vector<float> mAngles;

    int mXP;             // experience points
    int mHP;             // hit points
    int mHealth;         // health
    int mLevel;          // level
    int mScore;          // score
    double mPlayerSpeed; // speed
    double mBulletSpeed; // bullet speed
};

#endif