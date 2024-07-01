#pragma once

#include "Console.hpp"
#include "FpsCounter.hpp"
#include <list>

class System
{
public:
    std::list<std::string> hudIds;
    const unsigned int windowWidth;
    const unsigned int windowHeight;

    sf::Font font;
    sf::RenderWindow window;

    
    Console console;
    FpsCounter counter;

    System();

    const std::string getUnicalId();
    bool isIdUnical(std::string id);

    ~System();
};

System::System() : windowWidth(1600), windowHeight(900), counter(windowWidth), window(sf::VideoMode(windowWidth, windowHeight), "Game", sf::Style::Default)
{
    window.setFramerateLimit(60);
    font.loadFromFile("Resources/Fonts/JetBrainsMono-Medium.ttf");
    console.setFont(font);
    counter.setFont(font);
    console.setWindow(window);
}

const std::string System::getUnicalId()
{
    std::string id;
    for (int i = 0; i < 5; i++)
    {
        id += std::to_string(rand() % 10 + '0');
    }
    return id;
}

bool System::isIdUnical(std::string id)
{
    for (auto i : hudIds)
    {
        if (i == id) return false;
    }
    return true;
}

System::~System() { }

System BaS;