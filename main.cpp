#define WINDOW_WIDTH 1600
#define WINDOW_HEIGHT 900

#include "Header.hpp"
#include "InternalServer/Event/EventHandler.hpp"
#include "Game/Game.hpp"
#include "Resources/CvsReader.hpp"

// Bravery and Stupidi* args */ty

int main()
{   
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game", sf::Style::Default);

	window.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("Resources/Fonts/JetBrainsMono-Medium.ttf");

    Game game(window);

    game.setFont(font);

    game.run();
}