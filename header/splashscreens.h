#ifndef SPLASHSCREENS_H
#define SPLASHSCREENS_H

#include <SFML/Graphics.hpp>
#include <stdexcept>

/**
 * @brief This struct handles the splash screen for the game.
 *
 */
struct SplashScreen
{
    sf::Texture mTexture; // Texture for the splash screen
    sf::Sprite mSprite;   // Sprite for the splash screen

    sf::Font mFont;    // Font for the splash screen text
    sf::Text mPrompt;  // blinking “Press Enter/gameover”
    sf::Text mPrompt2; // press enter (to replay)

    float mBlinkTimer = 0.f;         // Timer for blinking effect
    bool mShowPrompt = true;         // Flag to show/hide prompt text
    const float BLINK_PERIOD = 0.5f; // Blink period in seconds

    /**
     * @brief Construct a new Splash Screen object
     *
     * @param texturePath The path to the splash screen texture
     * @param fontPath The path to the font file
     */
    SplashScreen(const std::string &texturePath,
                 const std::string &fontPath)
    {
        // Load splash image/ error handling
        if (!mTexture.loadFromFile(texturePath))
        {
            throw std::runtime_error("Failed to load splash texture");
        }
        mSprite.setTexture(mTexture);

        // Load font & setup prompt text /error handling
        if (!mFont.loadFromFile(fontPath))
        {
            throw std::runtime_error("Failed to load font");
        }
        mPrompt.setFont(mFont);
        mPrompt2.setFont(mFont);
        mPrompt.setString("Press Enter to Start"); // default text
        mPrompt.setCharacterSize(32);
        mPrompt.setFillColor(sf::Color::White);

        // Center prompt in an 800×800 window
        auto tb = mPrompt.getLocalBounds();
        mPrompt.setOrigin(tb.left + tb.width / 2.f,
                          tb.top + tb.height / 2.f);
        mPrompt.setPosition(400.f, 600.f);
    }

    /**
     * @brief This function displays the splash screen and handles user input.
     *
     * @param window The render window to display the splash screen
     */
    void display(sf::RenderWindow &window)
    {
        sf::Clock clock;
        while (window.isOpen())
        {
            float dt = clock.restart().asSeconds();

            // Handle close / Enter
            sf::Event evt;
            while (window.pollEvent(evt))

            {
                // ensure windows close and game/program exits cleanly
                if (evt.type == sf::Event::Closed)
                {
                    window.close();
                    exit(0);
                }
                if (evt.type == sf::Event::KeyPressed && evt.key.code == sf::Keyboard::Enter)
                {
                    return; // exit splash
                }
            }

            // Blink the prompt text
            mBlinkTimer += dt * .8f;
            if (mBlinkTimer >= BLINK_PERIOD)
            {
                mBlinkTimer -= BLINK_PERIOD;
                mShowPrompt = !mShowPrompt;
            }

            // Render splash
            window.clear();
            window.draw(mSprite);
            // needed for blinking logic text
            if (mShowPrompt)
            {
                window.draw(mPrompt);
            }
            window.draw(mPrompt2);
            window.display();
        }
    }
};

#endif // SPLASHSCREENS_H
