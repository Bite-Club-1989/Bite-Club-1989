#ifndef HUD_HPP
#define HUD_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>
/**
 * @brief Heads up display class that handles the health bar, level, ammo, stamina, and points
 *
 */
class Hud
{
public:

    Hud(); // Constructor


    void setCurrHealth(int h);  // Set current health
    void setCurrPower(int p);   // Set current power
    void setCurrLevel(int l);   // Set current level
    void setCurrBullets(int b); // Set current bullets
    void setCurrPoints(int p);  // Set current points
    void resetCurrPoints();     // Reset current points

    const sf::RectangleShape &getHealthBar() const { return healthBar; }    // Get health bar
    const sf::RectangleShape &getPowerupBar() const { return powerupBar; }; // Get powerup bar
    const sf::Text &getLevelText() const { return mLevel; };                // Get level text
    const sf::Text &getBulletText() const { return mBullet; };              // Get bullet text
    const sf::Text &getPointText() const { return mPoint; };                // Get point text

private:
    sf::RectangleShape healthBar;  // Health bar
    sf::RectangleShape powerupBar; // Powerup bar
    sf::Font mFont;                // Font for text
    sf::Text mLevel;               // Player level
    sf::Text mBullet;              // Player bullets
    sf::Text mPoint;               // Player points

    int currHealth;  // Current health
    int currPower;   // Current power
    int currLevel;   // Current level
    int currBullets; // Current bullets
    int currPoints;  // Current points

    void updateHealthBar();  // Update health bar
    void updatePowerupBar(); // Update powerup bar
    void updateLevelText();  // Update level text
    void updateBulletText(); // Update bullet text
    void updatePointText();  // Update point text

};

#endif