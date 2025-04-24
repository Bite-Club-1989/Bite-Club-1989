#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "enemy.hpp"
#include "weapon.h"
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

    float mDT;

    std::vector<Enemy> Enemies;

private:
    void resetGame(); // allows for restarting game
    Player player1;
    Enemy enemy1;
    int LEVEL = 1;
    int lastSpawnedLevel = 0;

    sf::RenderWindow mWindow;
    sf::Texture mBackground;
    sf::Sprite mSpriteBackground;
    bool mIsDone;
    sf::Music mMusic;
    // add button for quick restart
   
};

#endif