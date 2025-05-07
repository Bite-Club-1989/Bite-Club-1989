/**
 * @file game.h
 * @authors Chris Joe and Tyler
 * @brief 
 * @version 0.1
 * @date 05-06-2025
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "enemy.hpp"
#include "weapon.h"
#include "hud.hpp"
#include "splashscreens.h"
#include <SFML/Audio.hpp>

/**
 * @brief Game class that handles the game loop, input, update, and rendering.
 * 
 */
class Game
{
public:
    Game();
    ~Game() {};

    void handleInput(); //from user
    void update(float); // update all game objects and logic
    void render(); //render sprites to window
    bool isDone() const; // game is done
    void updateCamView(); //move camera perspective to player
    void checkProjCollision(); // check collisions progectiles and enemy vector
    void checkAllEnemiesDead(); // check if all enemies dead to increase level
    void playSplash(); // play splash screen
    void resetGame(); // reset all game variables/ obiects
    void playEnd(); //play end screen 
    void separateEnemies(); // keep enemies from 100% overlapping
    float mDT;

private:
    Player player1;
    std::vector<Enemy> Enemies;
    Enemy e;
    sf::Vector2f randomSpawn(int i);

    int LEVEL = 1;
    int lastSpawnedLevel = 0;
    float spawnTimer = 0.f;
    float spawnDuration = 5.f;

    Hud hudOverlay;

    sf::RenderWindow mWindow;
    sf::Texture mBackground;
    sf::Texture mRoofOne;
    sf::Sprite mSpriteBackground;
    sf::View view = mWindow.getDefaultView();
    sf::Music mMusic;
    sf::Music mSplashMusic;
    bool mIsDone;

    // add button for quick restart
};

#endif