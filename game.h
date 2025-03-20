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
    void update();
    void render();
    bool isDone() const;


private:
    Player player1;
    sf::RenderWindow mWindow;
    bool mIsDone;
};

#endif