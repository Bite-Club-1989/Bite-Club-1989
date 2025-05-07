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

    Game(); // Constructor

    void handleInput();         // Handle input from the player
    void update(float);         // Update the game state
    void render();              // Render the game
    bool isDone() const;        // Check if the game is done
    void updateCamView();       // Update the camera view
    void checkProjCollision();  // Check for projectile collisions
    void checkAllEnemiesDead(); // Check if all enemies are dead
    void playSplash();          // Play the splash screen
    void resetGame();           // Reset the game state
    void playEnd();             // Play the end screen
    void separateEnemies();     // Separate enemies from each other
    float mDT;                  // delta time

private:
    Player player1;                  // Player object
    std::vector<Enemy> Enemies;      // Vector of enemy objects
    Enemy e;                         // Enemy object for spawning
    sf::Vector2f randomSpawn(int i); // Random spawn position for enemies

    int LEVEL = 1;             // Current level
    int lastSpawnedLevel = 0;  // Last level spawned
    float spawnTimer = 0.f;    // Timer for spawning enemies
    float spawnDuration = 5.f; // Duration for spawning enemies

    Hud hudOverlay; // HUD overlay object

    sf::RenderWindow mWindow;                 // Render window object
    sf::Texture mBackground;                  // Background texture
    sf::Texture mRoofOne;                     // Roof texture
    sf::Sprite mSpriteBackground;             // Background sprite
    sf::Sprite mSpriteRoofOne;                // Roof sprite
    sf::View view = mWindow.getDefaultView(); // Camera view
    sf::Music mMusic;                         // Background music
    sf::Music mSplashMusic;                   // Splash screen music
    bool mIsDone;                             // Game state

};

#endif