#include "../header/game.h"
#include "../header/player.hpp"
#include "../header/weapon.h"
#include "../header/hud.hpp"
#include <ctime>

Game::Game() : mWindow(sf::VideoMode(800, 800), "Bite Club 1989"), player1()
{
    mIsDone = false;

    // can add soundtrack(s) here
    if (!mMusic.openFromFile("../assets/sounds/For Whom The Bell Tolls (Remastered).mp3"))
    {
        std::cerr << "Failed to load music\n";
    }
    else
    {
        mMusic.setLoop(true);
        mMusic.play();
    }

    mBackground.loadFromFile("../assets/textures/topDown.png");

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
    updateCamView();
    mWindow.clear(sf::Color::Black);

    // Draw world
    mWindow.draw(mSpriteBackground);
    player1.draw(mWindow, mDT);

    // loop through all enemies to draw and check damage
    for (std::size_t i = 0; i < Enemies.size(); i++)
    {
        Enemies[i].updateAndDraw(mWindow, player1, mDT);
        Enemies[i].enemyDealDamage(player1);
    }

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
    }
}

void Game::playSplash()
{
    SplashScreen splash(
        "../assets/textures/splash/transitions/image0.jpg",
        "../assets/fonts/Meta-Courage-TTF.ttf");

    splash.display(mWindow);
}
