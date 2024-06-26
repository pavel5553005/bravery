#ifndef Console_hpp_
#define Console_hpp_
#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include "../InternalServer/Position/Coordinates.hpp"
#include "../InternalServer/Position/Vector2d.hpp"

class Console
{
private:
    struct ConsoleText
    {
        std::string text;
        unsigned int time;
        sf::Color color;
    };
    sf::RenderWindow* window;
    sf::Font font;
    std::list<ConsoleText*> console;
public:
    Console();

    void setWindow(sf::RenderWindow& window);
    void setFont(sf::Font& font);

    void log(std::string text, sf::Color color = sf::Color::White);
    void errorLog(std::string text);
    void drawConsole();

    ~Console();
};

Console::Console()
{
    this->window = nullptr;
}

void Console::setWindow(sf::RenderWindow& window) { this->window = &window; }

void Console::setFont(sf::Font& font) { this->font = font; }

void Console::log(std::string text, sf::Color color)
{
    ConsoleText* consoleText = new ConsoleText;
    consoleText->text = text;
    consoleText->color = color;
    consoleText->time = 0;
    console.push_back(consoleText);

    if (console.size() > 20)
    {
        console.pop_front();
    }
}

void Console::errorLog(std::string text) { log("Error: " + text, sf::Color(255, 128, 128)); }

void Console::drawConsole()
{
    int index = 0;
    for (auto i : console)
    {
        if (i->time >= 600) continue;
        i->time++;
        

        sf::RectangleShape rect(sf::Vector2f(i->text.length() * 10, 16));
        rect.setPosition(0, index * 16);

        sf::Text text;
        text.setFont(font);
        text.setString(i->text);
        text.setCharacterSize(16);
        if (i->time < 515)
        {
            text.setFillColor(i->color);
            rect.setFillColor(sf::Color::Black);
        }
        else
        {
            text.setFillColor(sf::Color(i->color.r, i->color.g, i->color.b, (600 - i->time) * 3));
            rect.setFillColor(sf::Color(0, 0, 0, (600 - i->time) * 3));
        }
        text.setPosition(0, index * 16 - 3);
        window->draw(rect);
        window->draw(text);
        index++;
    }
}

Console::~Console() { }

#endif