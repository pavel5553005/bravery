#include "Header.hpp"
#include "InternalServer/Event/EventHandler.hpp"
#include "Game/Game.hpp"
#include "Resources/CvsReader.hpp"

// Bravery and Stupidity


int main()
{
    const int windowWidth = 1600;
    const int windowHeight = 900;
    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game", sf::Style::Default);

	window.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("Resources/Fonts/JetBrainsMono-Medium.ttf");

    Game game(windowWidth, windowHeight, window);

    game.setFont(font);

    game.run();
}