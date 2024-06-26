#pragma once
#include "Console.hpp"
#include "FpsCounter.hpp"

class System
{
private:
    
public:
    const unsigned int windowWidth;
    const unsigned int windowHeight;

    sf::Font font;
    sf::RenderWindow window;

    
    Console console;
    FpsCounter counter;

    System();
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

System::~System() { }

System BaS;