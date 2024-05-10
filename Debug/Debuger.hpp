#ifndef Debuger_hpp_
#define Debuger_hpp_
#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include "../InternalServer/Position/Coordinates.hpp"
#include "../InternalServer/Position/Vector2d.hpp"

class Debuger
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
    Debuger();

    void setWindow(sf::RenderWindow* window);
    void setFont(sf::Font& font);

    void consoleLog(std::string text, sf::Color color = sf::Color::White);
    void errorLog(std::string text);
    void drawConsole();

    ~Debuger();
};

#include "Debuger.cpp"

#endif