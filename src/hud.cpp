/**
 * @file hud.cpp
 * @author ...
 * @brief This file contains the implementation of the Hud class, which is responsible for displaying the HUD (Heads-Up Display) in the game.
 * @version 0.1
 * @date 2025-05-06
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "../header/hud.hpp"

/**
 * @brief Construct a new Hud:: Hud object
 *
 */
Hud::Hud()
{
    // assets/fonts/Meta-Courage-TTF.ttf
    if (!mFont.loadFromFile("../assets/fonts/Meta-Courage-TTF.ttf"))
        throw std::runtime_error("Failed to load font");

    // Set variables
    currLevel = 1;
    currBullets = 0;
    currPoints = 0;
    currHealth = 100;
    currPower = 100;

    // Health Bar
    healthBar.setSize(sf::Vector2f(100, 10));
    healthBar.setPosition(10, 10);
    sf::Color healthBarColor = sf::Color(255, 0, 0);
    healthBar.setFillColor(healthBarColor);
    mHealth.setFont(mFont);
    mHealth.setCharacterSize(10);
    mHealth.setPosition(120, 10);
    mHealth.setFillColor(sf::Color::White);
    updateHealthText();

    // Power-up Bar
    powerupBar.setSize(sf::Vector2f(100, 10));
    powerupBar.setPosition(10, 22);
    sf::Color powerupBarColor = sf::Color(0, 255, 255);
    powerupBar.setFillColor(powerupBarColor);
    mPowerup.setFont(mFont);
    mPowerup.setCharacterSize(10);
    mPowerup.setPosition(120, 22);
    mPowerup.setFillColor(sf::Color::White);
    updatePowerUpText();

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
    mPoint.setPosition(330, 10);
    mPoint.setFillColor(sf::Color::White);
    updatePointText();
};

/**
 * @brief This function sets the current health of the player and updates the health bar
 *
 * @param h The current health of the player
 */
void Hud::setCurrHealth(int h)
{
    currHealth = h;
    updateHealthBar();
    updateHealthText();
}

/**
 * @brief This function sets the current power of the player and updates the power-up bar
 *
 * @param p The current power of the player
 */
void Hud::setCurrPower(int p)
{
    currPower = p;
    updatePowerupBar();
    updatePowerUpText();
}

/**
 * @brief This function sets the current level of the player and updates the level text
 *
 * @param l The current level of the player
 */
void Hud::setCurrLevel(int l)
{
    currLevel = l;
    updateLevelText();
};

/**
 * @brief This function sets the current bullets of the player and updates the bullet text
 *
 * @param b The current bullets of the player
 */
void Hud::setCurrBullets(int b)
{
    currBullets = b;
    updateBulletText();
};

/**
 * @brief This function sets the current points of the player and updates the point text
 *
 * @param p The current points of the player
 */
void Hud::setCurrPoints(int p)
{
    currPoints += p;
    updatePointText();
};

/**
 * @brief This function resets the current points of the player to 0 and updates the point text
 *
 */
void Hud::resetCurrPoints()
{
    currPoints = 0;
    updatePointText();
}

/**
 * @brief This function updates the health bar with the current health of the player
 *
 */
void Hud::updateHealthBar()
{
    healthBar.setSize(sf::Vector2f(currHealth, 10));
    healthBar.setPosition(10, 10);
    sf::Color healthBarColor = sf::Color(255, 0, 0);
    healthBar.setFillColor(healthBarColor);
}

/**
 * @brief This function updates the power-up bar with the current power of the player
 *
 */
void Hud::updatePowerupBar()
{
    powerupBar.setSize(sf::Vector2f(currPower, 10));
    powerupBar.setPosition(10, 22);
    sf::Color powerupBarColor = sf::Color(0, 255, 255);
    powerupBar.setFillColor(powerupBarColor);
}

/**
 * @brief This function updates the level text with the current level of the player
 *
 */
void Hud::updateLevelText()
{
    mLevel.setString("Level: " + std::to_string(currLevel));
}

/**
 * @brief This function updates the bullet text with the current bullets of the player
 *
 */
void Hud::updateBulletText()
{
    mBullet.setString("Ammo: " + std::to_string(currBullets) + "/30");
}

/**
 * @brief This function updates the point text with the current points of the player
 *
 */
void Hud::updatePointText()
{
    mPoint.setString("Points: " + std::to_string(currPoints));
}

/**
 * @brief This function updates the health text with the current health of the player
 *
 */
void Hud::updateHealthText()
{
    mHealth.setString(std::to_string(currHealth) + "/100");
}

/**
 * @brief This function updates the power-up text with the current power of the player
 *
 */
void Hud::updatePowerUpText()
{
    mPowerup.setString(std::to_string(currPower) + "/100");
}
