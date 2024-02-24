#ifndef Debuger_hpp_
#define Debuger_hpp_
#include <SFML/Graphics.hpp>
#include <string>
#include <list>
#include "../InternalServer/Position/Coordinates.hpp"
#include "../InternalServer/Position/Vector2d.hpp"

class Camera;

class Debuger
{
private:
    struct ConsoleText
    {
        std::string text;
        unsigned int time;
    };
    sf::RenderWindow* window;
    sf::Font font;
    Camera* camera;
    std::list<ConsoleText*> console;
public:
    Debuger();

    void setCamera(Camera* camera);
    void setWindow(sf::RenderWindow* window);
    void setFont(sf::Font& font);

    void consoleLog(std::string text);
    void drawRectangle(sf::Color color, Coordinates pos, Vector2d size);
    void drawConsole();

    ~Debuger();
};

#endif