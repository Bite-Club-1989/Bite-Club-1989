#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "enemy.hpp"
#include "weapon.h"
#include "hud.hpp"
#include "splashscreens.h"
#include <SFML/Audio.hpp>

class Game
{
public:
    Game();
    ~Game() {};

    void handleInput();
    void update(float);
    void render();
    bool isDone() const;
    void updateCamView();
    void checkProjCollision();
    void checkAllEnemiesDead();
    void playSplash();
    void resetGame();
    void playEnd();
    void separateEnemies();
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
    sf::Sprite mSpriteRoofOne;
    sf::View view = mWindow.getDefaultView();
    sf::Music mMusic;
    sf::Music mSplashMusic;
    bool mIsDone;

    // add button for quick restart
};

#endif