/**
 * @file game.cpp
 * @author ...
 * @brief This file contains the implementation of the Game class, which is responsible for managing the game state, rendering, and handling input.
 * @version 0.1
 * @date 2025-05-06
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "../header/game.h"
#include "../header/player.hpp"
#include "../header/weapon.h"
#include "../header/hud.hpp"
#include <SFML/System.hpp>
#include <ctime>
#include <cstdlib>


/**
 * @brief Construct a new Game:: Game object
 *
 */
Game::Game() : mWindow(sf::VideoMode(800, 800), "Bite Club 1989"), player1()
{
    mIsDone = false;

    mBackground.loadFromFile("../assets/textures/topDown2.png");

    mSpriteBackground.setTexture(mBackground);
    mSpriteBackground.setOrigin(0, 0);
    mSpriteBackground.setScale(1, 1);

    view.setSize(800.f, 800.f);
}


/**
 * @brief This function handles the input for the game
 *
 */
void Game::handleInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {

        if (event.type == sf::Event::Closed)
        {
            mSplashMusic.stop();
            mMusic.stop();
            mWindow.close();
            std::exit(0);
        }
    }
}


/**
 * @brief This function updates the game state
 *
 * @param dt The delta time since the last frame
 */
void Game::update(float dt)
{
    mDT = dt;
    // update splawned enemies if level changes
    if (LEVEL != lastSpawnedLevel)
    {
        // clear old enemies
        Enemies.clear();
        srand(time(NULL)); // random number seed
        // spawn new enemies based on level
        for (int i = 0; i < LEVEL * 3; ++i)
        {
            //spawn delay/stagger
            while (spawnDuration >= spawnTimer)
            {
                spawnTimer += dt;
            }
            // reset timer
            spawnTimer = 0.f;
            e.position(randomSpawn(i)); // set position 
            Enemies.push_back(e); //push back new enemy into vector
        }
        lastSpawnedLevel = LEVEL; //set last level to current level
    }
    // if player is dead, end game
    if (player1.mState == Entity::EntityState::Dead)
    {
        mIsDone = true;
        while (Enemies.size())
        {
            Enemies.pop_back();
        }
    }
    // keep enemies from overlapping
    separateEnemies();
}


/**
 * @brief This function renders the game
 *
 */
void Game::render()
{
    updateCamView(); //to player position
    mWindow.clear(sf::Color::Black);

    // Draw world
    mWindow.draw(mSpriteBackground);

    // loop through all enemies to draw and check damage
    // draw dead enemies first
    for (std::size_t i = 0; i < Enemies.size(); i++)
    {
        if (Enemies[i].mState == Entity::EntityState::Dead)
        {
            Enemies[i].updateAndDraw(mWindow, player1, mDT);
        }
    }
    // draw alive enemies on top
    for (std::size_t i = 0; i < Enemies.size(); i++)
    {
        if (Enemies[i].mState == Entity::EntityState::Alive)
        {
            Enemies[i].updateAndDraw(mWindow, player1, mDT);
            Enemies[i].enemyDealDamage(player1);
        }
    }

    // Draw player
    player1.draw(mWindow, mDT);
    // check bullet collisions
    checkProjCollision();
    // check if all enemies are dead (level up)
    checkAllEnemiesDead();

    // Set hud from player stats
    hudOverlay.setCurrPower(player1.getStamina());
    hudOverlay.setCurrBullets(30 - player1.getWeapon().mBulletsFired);
    hudOverlay.setCurrHealth(player1.getHealth());

    mWindow.setView(mWindow.getDefaultView());

    // Draw HUD Display
    mWindow.draw(hudOverlay.getHealthBar());
    mWindow.draw(hudOverlay.getPowerupBar());
    mWindow.draw(hudOverlay.getLevelText());
    mWindow.draw(hudOverlay.getBulletText());
    mWindow.draw(hudOverlay.getPointText());

    mWindow.display();
}


/**
 * @brief This function checks if the game is done
 *
 * @return true True if the game is done
 * @return false True if the game is not done
 */
bool Game::isDone() const
{
    return (!mWindow.isOpen() || mIsDone);
}


/**
 * @brief This function updates the camera view based on the player position
 *
 */
void Game::updateCamView()
{
    sf::FloatRect bounds = player1.mSprite.getGlobalBounds();
    sf::Vector2f playerCenter(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

    // View & world sizes
    sf::Vector2f viewSize = view.getSize();
    sf::Vector2f worldSize(1200.f, 1000.f);

    // Camera center to avoid view going outside the map
    sf::Vector2f centerCam = playerCenter;

    float halfWidth = viewSize.x / 2.f;
    float halfHeight = viewSize.y / 2.f;

    // Logic to avoid camera view outside the map
    if (playerCenter.x < halfWidth)
    {
        centerCam.x = halfWidth;

    }
    else if (playerCenter.x > worldSize.x - halfWidth)
    {

        centerCam.x = worldSize.x - halfWidth;
    }

    if (playerCenter.y < halfHeight)
    {
        centerCam.y = halfHeight;

    }
    else if (playerCenter.y > worldSize.y - halfHeight)
    {
        centerCam.y = worldSize.y - halfHeight;

    }

    view.setCenter(centerCam);
    mWindow.setView(view);
}


/**
 * @brief This function checks for projectile collision with enemies
 *
 */
void Game::checkProjCollision()
{
    std::vector<Weapon::Projectile> &projectiles = player1.getWeapon().mProjectiles;
    for (int i = 0; i < static_cast<int>(projectiles.size()); i++)
    {
        if (projectiles[i].mState == Weapon::Projectile::BulletState::Disabled)
            continue; // SKIP LOOP
        for (std::size_t j = 0; j < Enemies.size(); j++)
        {
            if (Enemies[j].mState == Entity::EntityState::Dead)
                continue; // SKIP LOOP
            if (Enemies[j].mSprite.getGlobalBounds().intersects(projectiles[i].bullet.getGlobalBounds()))
            {
                Enemies[j].takeDamage(player1.getWeapon().getWepDmg());

                if (Enemies[i].mState == Entity::EntityState::Dead)
                    hudOverlay.setCurrPoints(15); // Extra points on death
                else
                    hudOverlay.setCurrPoints(5); // Normal hit points

                projectiles.erase(projectiles.begin() + i);
                --i;
                break;
            }
        }
    }
}


/**
 * @brief This function checks if all enemies are dead
 *
 */
void Game::checkAllEnemiesDead()
{
    // if enemies are alldead level up
    bool allDead = true;
    for (std::size_t i = 0; i < Enemies.size(); i++)
    {
        if (Enemies[i].mState == Entity::EntityState::Alive) // if any alive
            allDead = false;
    }

    if (allDead)
    {
        ++LEVEL;
        hudOverlay.setCurrLevel(LEVEL);
        player1.mHealth = 100;
    }
}


/**
 * @brief This function plays the splash screen and music
 *
 */
void Game::playSplash()
{
    // load & play splash only and error handling
    if (!mSplashMusic.openFromFile("../assets/sounds/Intro storm.mp3"))
    {
        std::cerr << "Failed to load splash music\n";
    }
    mSplashMusic.setLoop(false);
    mSplashMusic.play();
    mSplashMusic.setVolume(75.f);

    // display the screen (blocks until Enter is pressed) image and font
    SplashScreen splash("../assets/textures/splash/transitions/image0.jpg", "../assets/fonts/Meta-Courage-TTF.ttf");
    splash.display(mWindow);

    //stop splash and immediately start game music
    mSplashMusic.stop();

    if (!mMusic.openFromFile("../assets/sounds/For Whom The Bell Tolls (Remastered).mp3"))
        std::cerr << "Failed to load game music\n";
    mMusic.setLoop(true);
    mMusic.setVolume(50.f);
    mMusic.play();
}


/**
 * @brief This function plays the end screen and music
 *
 */
void Game::playEnd()
{
    SplashScreen splash("../assets/textures/splash/transitions/image0.jpg", "../assets/fonts/Meta-Courage-TTF.ttf");

    // set text variables
    splash.mSprite.setColor(sf::Color::Red);

    splash.mPrompt.setString("GAME OVER");
    splash.mPrompt.setCharacterSize(50);
    sf::FloatRect bounds = splash.mPrompt.getLocalBounds();
    // center the origin
    splash.mPrompt.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);

    // get the window size
    sf::Vector2u windowSize = mWindow.getSize();
    // position it
    splash.mPrompt.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 40.f);

    splash.mPrompt2.setString("Play Again? (ENTER)");
    splash.mPrompt2.setCharacterSize(32);
    sf::FloatRect bounds2 = splash.mPrompt2.getLocalBounds();
    splash.mPrompt2.setOrigin(bounds2.left + bounds2.width / 2.f, bounds2.top + bounds2.height / 2.f);
    splash.mPrompt2.setPosition(windowSize.x / 2.f, windowSize.y / 2.f + 20.f);
    splash.display(mWindow);
}


/**
 * @brief This function resets the game state
 *
 */
void Game::resetGame()
{
    mIsDone = false;
    player1.changeState(Entity::EntityState::Alive);
    player1.health(100);
    while (Enemies.size())
    {
        Enemies.pop_back();
    }

    LEVEL = 1;
    lastSpawnedLevel = 0;
    hudOverlay.setCurrLevel(LEVEL);
    hudOverlay.resetCurrPoints();
    player1.getWeapon().setBulletsFired(0);
}


/**
 * @brief This function generates a random spawn point for the enemies
 *
 * @param i The index of the enemy
 * @return sf::Vector2f The random spawn point
 */
sf::Vector2f Game::randomSpawn(int i)
{
    int randomNumber = (rand() % 4) + 1; // rand num 1-4
    if (randomNumber == 1)
    {
        return sf::Vector2f({0.f + (50.f * (i)), 0.f});
    }
    else if (randomNumber == 2)
    {
        return sf::Vector2f({0.f + (50.f * (i)), 1000.f});
    }
    else if (randomNumber == 3)
    {
        return sf::Vector2f({1200.f, 0.f + (50.f * (i))});
    }
    else
    {
        return sf::Vector2f({1200.f, 1000.f - (50.f * i)});
    }
}


/**
 * @brief This function separates the enemies to avoid overlap
 *
 */
void Game::separateEnemies()
{
    const float minDist = 20.f; // desired minimum spacing
    const float minDist2 = minDist * minDist;
    const float pushStr = 0.5f; // how hard to push them apart


    for (size_t i = 0; i < Enemies.size(); ++i)
    {
        for (size_t j = i + 1; j < Enemies.size(); ++j)
        {
            auto &A = Enemies[i].mSprite; //auto data type set a and b
            auto &B = Enemies[j].mSprite;
            // subtract the positions of the two sprites to get the distance vector
            sf::Vector2f d = A.getPosition() - B.getPosition();

            float dist2 = d.x * d.x + d.y * d.y;
            if (dist2 > 0 && dist2 < minDist2 && Enemies[i].mState == Entity::EntityState::Alive && Enemies[j].mState == Entity::EntityState::Alive)

            {
                float dist = std::sqrt(dist2); // finish pythag
                // normalized direction
                d /= dist; // normalize the distance vector
                float overlap = (minDist - dist) * pushStr; // calculate overlap
                // push each sprite half the overlap in opposite directions

                A.move(d * (overlap * 0.5f));
                B.move(-d * (overlap * 0.5f));

            }
        }
    }
}
