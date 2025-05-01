#include "../header/enemy.hpp"

// Deals damage to the player if their sprites intersect
void Enemy::enemyDealDamage(Player &p)
{
    if (p.mState == Entity::EntityState::Dead)
        return;
    if (mDamageClock.getElapsedTime().asSeconds() >= mDamageRate)
    {
        if (p.mSprite.getGlobalBounds().intersects(mSprite.getGlobalBounds()) && mState == EntityState::Alive)
        {
            std::cout << "Player Hit" << std::endl;
            p.takeDamage(10);
        }
        mDamageClock.restart();
    }
}

// Updates enemy movement toward the player using delta time.
void Enemy::enemyMove(Player &p, float dt)
{
    // Get positions
    // Initialize vector 2f with enemy position
    sf::Vector2f enemyPos = mSprite.getPosition();
    // Initialize vector 2f with player position
    sf::Vector2f playerPos = p.mSprite.getPosition();

    // Find direction the enemy should move to intercept the player
    sf::Vector2f direction = playerPos - enemyPos;

    // Normalize the direction vector
    // calculate the length of the vector using Pythag ttheorem
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0)
    {
        // normalize the vector by dividing by length
        // can be adjusted later to vary chase speed and direction
        direction /= length;
    }

    // Move enemy along the normalized direction.
    // multiply to set speed diredtion with frame rate
    mSprite.move(direction * mSpeed * dt);
    // cout to verify movement
    // std::cout << "Enemy Position: " << mSprite.getPosition().x << ", " << mSprite.getPosition().y << std::endl;
}

// Override the base class draw method.
// This function must match the signature in Entity.
/* virtual void draw(sf::RenderWindow &window) override
{

   std::cout << "updating enemu" <<std:: endl;

   std::cout << "Drawing Enemy" << std::endl;
   window.draw(mSprite);
} */

// needed to create new function to be able to pass player object.
void Enemy::updateAndDraw(sf::RenderWindow &window, Player &p, float dt)
{
    if (mState == EntityState::Alive)
    {
        enemyMove(p, dt); // Update enemy position toward the player.
        updateHealthBar();
        window.draw(healthBar);
        window.draw(mSprite); // Draw the enemy.
    }
    else
    {
        enemyDeath(window);
    }
}
void Enemy::enemyDeath(sf::RenderWindow &window)
{
    mSprite.setTextureRect(sf::IntRect(0, 0, 35, 35));
    mSprite.setColor(sf::Color::Red);
    mSprite.setRotation(90);
    mSprite.move(0, 0);
    window.draw(mSprite);
    mState = EntityState::Dead;
}
