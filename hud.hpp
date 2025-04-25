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
        if (!mFont.loadFromFile("assets/fonts/Meta-Courage-TTF.ttf"))
            throw std::runtime_error("Failed to load font");

        // Set variables
        currLevel = 1;
        currBullets = 30;

        // Health Bar
        healthBar.setSize(sf::Vector2f(100, 10));
        healthBar.setPosition(10, 10);
        sf::Color healthBarColor = sf::Color(255, 0, 0);
        healthBar.setFillColor(healthBarColor);

        // Power-up Bar
        powerupBar.setSize(sf::Vector2f(100, 10));
        powerupBar.setPosition(10, 20);
        sf::Color powerupBarColor = sf::Color(0, 0, 255);
        powerupBar.setFillColor(powerupBarColor);

        // Level indicator
        mLevel.setFont(mFont);
        mLevel.setCharacterSize(20);
        mLevel.setPosition(10, 540);
        mLevel.setFillColor(sf::Color::White);
        updateLevelText();

        // Wpn / bullet indicator
        mBullet.setFont(mFont);
        mBullet.setCharacterSize(20);
        mBullet.setPosition(10, 560);
        mBullet.setFillColor(sf::Color::White);
        updateBulletText();
    };
    ~Hud() {};

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

    const sf::RectangleShape &getHealthBar() const { return healthBar; };
    const sf::RectangleShape &getPowerupBar() const { return powerupBar; };
    const sf::Text &getLevelText() const { return mLevel; }
    const sf::Text &getBulletText() const { return mBullet; }

private:
    sf::RectangleShape healthBar;
    sf::RectangleShape powerupBar;
    sf::Font mFont;
    sf::Text mLevel;
    sf::Text mBullet;

    int currLevel;
    int currBullets;

    void updateLevelText()
    {
        mLevel.setString("Level: " + std::to_string(currLevel));
    }

    void updateBulletText()
    {
        mBullet.setString("Ammo: " + std::to_string(currBullets) + "/30");
    }
};

#endif