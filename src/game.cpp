#include "../header/game.h"
#include "../header/player.hpp"
#include "../header/weapon.h"
#include "../header/hud.hpp"
#include <SFML/System.hpp>
#include <ctime>
#include <cstdlib>

Game::Game() : mWindow(sf::VideoMode(800, 800), "Bite Club 1989"), player1()
{
    mIsDone = false;

    mBackground.loadFromFile("../assets/textures/topDown2.png");

    mSpriteBackground.setTexture(mBackground);
    mSpriteBackground.setOrigin(0, 0);
    mSpriteBackground.setScale(1, 1);

    view.setSize(800.f, 800.f);
}

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
        for (int i = 0; i < LEVEL; ++i)
        {

            while (spawnDuration >= spawnTimer)
            {
                spawnTimer += dt;
            }
            // reset timer
            spawnTimer = 0.f;
            e.position(randomSpawn(i));
            Enemies.push_back(e);
        }
        lastSpawnedLevel = LEVEL;
    }
    if (player1.mState == Entity::EntityState::Dead)
    {
        mIsDone = true;
    }
}

void Game::render()
{
    updateCamView();
    mWindow.clear(sf::Color::Black);

    // Draw world
    mWindow.draw(mSpriteBackground);

    // loop through all enemies to draw and check damage
    for (std::size_t i = 0; i < Enemies.size(); i++)
    {
        Enemies[i].updateAndDraw(mWindow, player1, mDT);
        Enemies[i].enemyDealDamage(player1);
    }

    // Draw player
    player1.draw(mWindow, mDT);

    checkProjCollision();
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

bool Game::isDone() const
{
    return (!mWindow.isOpen() || mIsDone);
}

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
        centerCam.x = halfWidth;
    else if (playerCenter.x > worldSize.x - halfWidth)
        centerCam.x = worldSize.x - halfWidth;

    if (playerCenter.y < halfHeight)
        centerCam.y = halfHeight;
    else if (playerCenter.y > worldSize.y - halfHeight)
        centerCam.y = worldSize.y - halfHeight;

    view.setCenter(centerCam);
    mWindow.setView(view);
}

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

void Game::checkAllEnemiesDead()
{
    // if enemies are alldead level up
    bool allDead = true;
    for (std::size_t i = 0; i < Enemies.size(); i++)
    {
        if (Enemies[i].mState == Entity::EntityState::Alive)
            allDead = false;
    }

    if (allDead)
    {
        ++LEVEL;
        hudOverlay.setCurrLevel(LEVEL);
        player1.mHealth = 100;
    }
}

void Game::playSplash()
{
    // 1) load & play splash only
    if (!mSplashMusic.openFromFile("../assets/sounds/Intro storm.mp3"))
        std::cerr << "Failed to load splash music\n";
    mSplashMusic.setLoop(false);
    mSplashMusic.play();
    mSplashMusic.setVolume(75.f);

    // 2) display the screen (blocks until Enter)
    SplashScreen splash(
        "../assets/textures/splash/transitions/image0.jpg",
        "../assets/fonts/Meta-Courage-TTF.ttf");
    splash.display(mWindow);

    // 3) stop splash and immediately start game music
    mSplashMusic.stop();

    if (!mMusic.openFromFile("../assets/sounds/For Whom The Bell Tolls (Remastered).mp3"))
        std::cerr << "Failed to load game music\n";
    mMusic.setLoop(true);
    mMusic.setVolume(50.f);
    mMusic.play();
}

void Game::playEnd()
{
    SplashScreen splash(
        "../assets/textures/splash/transitions/image0.jpg",
        "../assets/fonts/Meta-Courage-TTF.ttf");

    // configure your two texts
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
