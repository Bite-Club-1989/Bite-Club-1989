#ifndef HUD_HPP
#define HUD_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>

class Hud
{
public:
    Hud()
    {
        // assets/fonts/Meta-Courage-TTF.ttf
        if (!mFont.loadFromFile("../assets/fonts/Meta-Courage-TTF.ttf"))
            throw std::runtime_error("Failed to load font");

        // Set variables
        currLevel = 1;
        currBullets = 0;
        currPoints = 0;

        // Health Bar
        healthBar.setSize(sf::Vector2f(100, 10));
        healthBar.setPosition(10, 10);
        sf::Color healthBarColor = sf::Color(255, 0, 0);
        healthBar.setFillColor(healthBarColor);

        // Power-up Bar
        powerupBar.setSize(sf::Vector2f(100, 10));
        powerupBar.setPosition(10, 22);
        sf::Color powerupBarColor = sf::Color(0, 255, 255);
        powerupBar.setFillColor(powerupBarColor);

        // Level indicator
        mLevel.setFont(mFont);
        mLevel.setCharacterSize(20);
        mLevel.setPosition(650, 10);
        mLevel.setFillColor(sf::Color::White);
        updateLevelText();

        // Wpn / bullet indicator
        mBullet.setFont(mFont);
        mBullet.setCharacterSize(20);
        mBullet.setPosition(650, 720);
        mBullet.setFillColor(sf::Color::White);
        updateBulletText();

        // Player points
        mPoint.setFont(mFont);
        mPoint.setCharacterSize(20);
        mPoint.setPosition(350, 10);
        mPoint.setFillColor(sf::Color::White);
        updatePointText();
    };
    ~Hud() {};

    void setCurrHealth(int h)
    {
        currHealth = h;
        updateHealthBar();
    }

    void setCurrPower(int p)
    {
        currPower = p;
        updatePowerupBar();
    }

    void setCurrLevel(int l)
    {
        currLevel = l;
        updateLevelText();
    };

    void setCurrBullets(int b)
    {
        currBullets = b;
        updateBulletText();
    };

    void setCurrPoints(int p)
    {
        currPoints += p;
        updatePointText();
    };

    const sf::RectangleShape &getHealthBar() const { return healthBar; };
    const sf::RectangleShape &getPowerupBar() const { return powerupBar; };
    const sf::Text &getLevelText() const { return mLevel; }
    const sf::Text &getBulletText() const { return mBullet; }
    const sf::Text &getPointText() const { return mPoint; }

private:
    sf::RectangleShape healthBar;
    sf::RectangleShape powerupBar;
    sf::Font mFont;
    sf::Text mLevel;
    sf::Text mBullet;
    sf::Text mPoint;

    int currHealth;
    int currPower;
    int currLevel;
    int currBullets;
    int currPoints;

    void updateHealthBar()
    {
        healthBar.setSize(sf::Vector2f(currHealth, 10));
        healthBar.setPosition(10, 10);
        sf::Color healthBarColor = sf::Color(255, 0, 0);
        healthBar.setFillColor(healthBarColor);
    }

    void updatePowerupBar()
    {
        powerupBar.setSize(sf::Vector2f(currPower, 10));
        powerupBar.setPosition(10, 22);
        sf::Color powerupBarColor = sf::Color(0, 255, 255);
        powerupBar.setFillColor(powerupBarColor);
    }

    void updateLevelText()
    {
        mLevel.setString("Level: " + std::to_string(currLevel));
    }

    void updateBulletText()
    {
        mBullet.setString("Ammo: " + std::to_string(currBullets) + "/30");
    }

    void updatePointText()
    {
        mPoint.setString("Points: " + std::to_string(currPoints));
    }
};

#endif