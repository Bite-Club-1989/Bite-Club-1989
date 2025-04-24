#include "game.h"
#include "player.hpp"
#include "weapon.h"
#include <ctime>
#include <thread>
#include <chrono>

Game::Game() : mWindow(sf::VideoMode(800, 800), "Bite Club 1989"), player1(), enemy1()
{
    mIsDone = false;
    //can add soundtrack(s) here
    if (!mMusic.openFromFile("assets/sounds/For Whom The Bell Tolls (Remastered).mp3")) {
        std::cerr << "Failed to load music\n";
    } else {
        mMusic.setLoop(true);
        mMusic.play();
    }
}

void Game::handleInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            mWindow.close();
            break;

        default:
            break;
        }
    }
}

void Game::update(float dt)
{
    mDT = dt;
    // update splawned enemies if level changes
    if (LEVEL != lastSpawnedLevel)
    {
        //clear old enemies
        Enemies.clear();
        // spawn new enemies based on level
        for (int i = 0; i < LEVEL; ++i)
        {
            Enemy e;
            // position them however you like:
            e.position({100.f * (i + 1), 100.f});
            Enemies.push_back(e);
        }
        lastSpawnedLevel = LEVEL;
    }
}

void Game::render()
{
    mWindow.clear(sf::Color::Black);

    // draw player
    player1.draw(mWindow, mDT);

    //loop through all enemies to draw and check damage
    for (auto &e : Enemies) 
    {
        e.updateAndDraw(mWindow, player1, mDT);
        e.enemyDealDamage(player1);
    }

    // check for colloisions beteen weapon attacks and enemies
    auto &projectiles = player1.getWeapon().getProjectiles();
    for (int i = 0; i < projectiles.size(); ++i) {
        if (!projectiles[i].checkIfActive()) continue;
        for (auto &e : Enemies) {
            if (e.mSprite.getGlobalBounds()
                   .intersects(projectiles[i].bullet.getGlobalBounds()))
            {
                e.takeDamage( player1.getWeapon().getWepDmg() );
                projectiles.erase(projectiles.begin() + i);
                --i;
                break;
            }
        }
    }

    // if enemies are alldead level uo
    bool allDead = std::all_of(Enemies.begin(), Enemies.end(),[](const Enemy &e)
    { return e.mState == Entity::EntityState::Dead; }
    );
    if (allDead) {
        ++LEVEL;
    }

    mWindow.display();
}


bool Game::isDone() const
{
    return (!mWindow.isOpen() || mIsDone);
}
