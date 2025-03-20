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

    void playerAttack();
    void playerDefend();
    void playerLevelUp();
    void playerWin();
    void playerScore();
    void playerHealth();
    void playerSpeed();
    void playerPosition();
    void playerExperience();
    void playerHitPoints();
    void playerLevel();

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
    PlayerState mState;
    PlayerAction mAction;
    std::vector<sf::CircleShape> mBullets;
    std::vector<float> angles;

    int mXP;       // experience points
    int mHP;       // hit points
    int mHealth;   // health
    int mLevel;    // level
    int mScore;    // score
    double mSpeed; // speed
};

#endif