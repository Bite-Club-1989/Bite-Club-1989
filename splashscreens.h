#ifndef SPLASHSCREENS_H
#define SPLASHSCREENS_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

struct SplashScreen
{

    sf::Texture mTexture;
    sf::SoundBuffer mSoundBuffer;
    sf::Sound mSound;
    float mDuration;
    sf::Sprite mOverlayObject;
    sf::Text mOverlayText;
    SplashScreen(const std::string &texturepath, const std::string &soundpath, float duration)
        : mTexture(), mSoundBuffer(), mSound(), mDuration(duration), mOverlayObject(), mOverlayText()
    {
        if (!mTexture.loadFromFile(texturepath))
        {
            throw std::runtime_error("Failed to load texture");
        }
        if (!mSoundBuffer.loadFromFile(soundpath))
        {
            throw std::runtime_error("Failed to load sound");
        }
        mSound.setBuffer(mSoundBuffer);
    };
    ~SplashScreen();
    void display(sf::RenderWindow &window);
    void setTexture(const std::string &texturepath);
    void setSound(const std::string &soundpath);
    void setDuration(float duration);
    void setPosition(float x, float y);
    void setScale(float x, float y);
    void setOverlayObject(const std::string &texturepath);
    void setOverlayPosition(float x, float y);
    void setOVerlayScale(float x, float y);
    void setOverlayColor(sf::Color color);
    void setOverlayText(const std::string &text, const std::string &fontpath, float size, sf::Color color, float x, float y);


};

#endif