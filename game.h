#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "player.hpp"

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
    sf::Clock mClock;

private:
    Player player1;
    sf::RenderWindow mWindow;
    sf::Texture mBackground;
    sf::Sprite mSpriteBackground;
    bool mIsDone;
};

#endif