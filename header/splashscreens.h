#ifndef SPLASHSCREENS_H
#define SPLASHSCREENS_H

#include <SFML/Graphics.hpp>
#include <stdexcept>

struct SplashScreen
{
    sf::Texture   mTexture;
    sf::Sprite    mSprite;

    sf::Font      mFont;
    sf::Text      mPrompt;         // blinking “Press Enter”
    float         mBlinkTimer  = 0.f;
    bool          mShowPrompt  = true;
    const float   BLINK_PERIOD = 0.5f;

    SplashScreen(const std::string& texturePath,
                 const std::string& fontPath)
    {
        // Load splash image
        if (!mTexture.loadFromFile(texturePath))
            throw std::runtime_error("Failed to load splash texture");
        mSprite.setTexture(mTexture);

        // Load font & setup prompt text
        if (!mFont.loadFromFile(fontPath))
            throw std::runtime_error("Failed to load font");
        mPrompt.setFont(mFont);
        mPrompt.setString("Press Enter to Start");
        mPrompt.setCharacterSize(32);
        mPrompt.setFillColor(sf::Color::White);

        // Center prompt in an 800×800 window
        auto tb = mPrompt.getLocalBounds();
        mPrompt.setOrigin(tb.left + tb.width/2.f,
                          tb.top  + tb.height/2.f);
        mPrompt.setPosition(400.f, 600.f);
    }

    // Block here until Enter is pressed
    void display(sf::RenderWindow& window)
    {
        sf::Clock clock;
        while (window.isOpen())
        {
            float dt = clock.restart().asSeconds();

            // Handle close / Enter
            sf::Event evt;
            while (window.pollEvent(evt))
            {
                if (evt.type == sf::Event::Closed)
                    window.close();
                if (evt.type == sf::Event::KeyPressed &&
                    evt.key.code == sf::Keyboard::Enter)
                {
                    // window.close(); // close window after enter is pressed
                    return;  // exit splash
                }
            }

            // Blink the prompt text
            mBlinkTimer += dt;
            if (mBlinkTimer >= BLINK_PERIOD)
            {
                mBlinkTimer -= BLINK_PERIOD;
                mShowPrompt = !mShowPrompt;
            }

            // Render splash
            window.clear();
            window.draw(mSprite);
            if (mShowPrompt)
                window.draw(mPrompt);
            window.display();
        }
    }
};

#endif // SPLASHSCREENS_H
