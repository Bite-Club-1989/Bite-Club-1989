#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "player.hpp"
#include "enemy.hpp"
#include "weapon.h"
#include "timer.hpp"

class Game
{
public:
    Game();
    ~Game() {};

    void handleInput();
    void update(float);
    void render(Timer &damageTimer);
    bool isDone() const;

    float mDT;

private:
    Player player1;
    Enemy enemy1;
    
    sf::RenderWindow mWindow;
    sf::Texture mBackground;
    sf::Sprite mSpriteBackground;
    bool mIsDone;
};

#endif