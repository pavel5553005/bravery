#include "Header.hpp"
#include "Game/Game.hpp"

int main()
{
    const int windowWidth = 1920;
    const int windowHeight = 1080;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game", sf::Style::Fullscreen);

    window.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf");

    Game game(windowWidth, windowHeight, window);

    game.setFont(font);

    game.run();
}

void drawTextLeft(sf::RenderWindow& window, sf::Font& font, std::string text, int index)
{
    sf::RectangleShape rect(sf::Vector2f(100, 15));
    rect.setPosition(0, index * 12);
    rect.setFillColor(sf::Color::Black);
    window.draw(rect);

    sf::Text textObj;
    textObj.setFont(font);
    textObj.setString(text);
    textObj.setCharacterSize(10);
    textObj.setFillColor(sf::Color::White);
    textObj.setPosition(0, index * 12);
    window.draw(textObj);
}