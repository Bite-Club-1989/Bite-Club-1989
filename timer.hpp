/**
 * @file player.hpp
 * @author Chris Bailey (cbailey@nic.edu)
 * @brief The timer class
 * @version 0.1
 * @date 2025-04-17
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef TIMER_HPP
#define TIMER_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include "timer.hpp"

class Timer
{
public:
    Timer(float delaySeconds) { delay = delaySeconds; }; // Default constructor
    ~Timer() {};                                         // Destructor

    // Functions
    bool ready()
    {
        if (clock.getElapsedTime().asSeconds() >= delay)
        {
            clock.restart();
            return true;
        }
        return false;
    };

    float restartAsSec() { return clock.restart().asSeconds(); };

private:
    float delay;
    sf::Clock clock;
};

#endif