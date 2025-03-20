#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

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
    sf::RenderWindow mWindow;
    bool mIsDone;
};

#endif