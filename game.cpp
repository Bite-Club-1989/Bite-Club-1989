#include "game.h"
#include "player.hpp"
#include "weapon.h"
#include <ctime>

Game::Game() : mWindow(sf::VideoMode(800, 800), "Bite Club 1989"), player1()
{
    mIsDone = false;

    // can add soundtrack(s) here
    if (!mMusic.openFromFile("assets/sounds/For Whom The Bell Tolls (Remastered).mp3"))
    {
        std::cerr << "Failed to load music\n";
    }
    else
    {
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
        // clear old enemies
        Enemies.clear();
        // spawn new enemies based on level
        for (int i = 0; i < LEVEL; ++i)
        {
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

    // loop through all enemies to draw and check damage
    int enemyVecSize = static_cast<int>(Enemies.size());
    for (int i = 0; i < enemyVecSize; i++)
    {
        Enemies[i].updateAndDraw(mWindow, player1, mDT);
        Enemies[i].enemyDealDamage(player1);
    }

    // check for colloisions beteen weapon attacks and enemies
    std::vector<Weapon::Projectile> &projectiles = player1.getWeapon().mProjectiles;
    for (int i = 0; i < static_cast<int>(projectiles.size()); i++)
    {
        if (projectiles[i].mState == Weapon::Projectile::BulletState::Disabled)
            continue; // SKIP LOOP
        for (int j = 0; j < enemyVecSize; j++)
        {
            if (Enemies[j].mState == Entity::EntityState::Dead)
                continue; // SKIP LOOP
            if (Enemies[j].mSprite.getGlobalBounds().intersects(projectiles[i].bullet.getGlobalBounds()))
            {
                Enemies[j].takeDamage(player1.getWeapon().getWepDmg());
                projectiles.erase(projectiles.begin() + i);
                --i;
                break;
            }
        }
    }

    // if enemies are alldead level uo
    bool allDead = true;
    for (int k = 0; k < enemyVecSize; k++)
        if (Enemies[k].mState == Entity::EntityState::Alive)
            allDead = false;
    if (allDead)
        ++LEVEL;

    mWindow.display();
}

bool Game::isDone() const
{
    return (!mWindow.isOpen() || mIsDone);
}

void Game::checkCollision()
{
}
