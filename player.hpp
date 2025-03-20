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
#include <SFML/Graphics.hpp>

class Player
{
public:
    Player();
    ~Player() {};

    void playerMove();
    void playerAttack();
    void playerDefend();
    void playerLevelUp();
    void playerDeath();
    void playerWin();
    void playerLose();
    void playerScore();
    void playerHealth();
    void playerSpeed();
    void playerPosition();
    void playerExperience();
    void playerHitPoints();
    void playerLevel();

    void draw(sf::RenderWindow& window);

private:
    sf::CircleShape mPlayer;
    //sf::RenderWindow mWindow;

    int xp;     // experience points
    int hp;     // hit points
    int health; // health
    int level;  // level
    int score;  // score
    int speed;  // speed
    int x;      // x position
    int y;      // y position
};

#endif