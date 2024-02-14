#include <SFML/Graphics.hpp>
#include "Map/Map.hpp"

int getTime();

void renderMap(sf::RenderWindow& window, Map* map);

int main()
{

    Map* map = new Map();

    const int windowWidth = 800;
    const int windowHeight = 600;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML window");

    window.setFramerateLimit(60);

    int startTime = 0;
    int endTime = 1;
    int fps = 0;
    
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");

    while (window.isOpen())
    {
        startTime = getTime();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        
        renderMap(window, map);

        sf::RectangleShape fpsBorder;
        fpsBorder.setSize(sf::Vector2f(30, 12));
        fpsBorder.setPosition(windowWidth - 30, 0);
        fpsBorder.setFillColor(sf::Color::Black);
        window.draw(fpsBorder);

        sf::Text fpsText;
        fpsText.setFont(font);
        fpsText.setString(std::to_string(fps));
        fpsText.setCharacterSize(10);
        fpsText.setFillColor(sf::Color::Green);
        fpsText.setPosition(windowWidth - 30, 0);
        window.draw(fpsText);

        window.display();

        endTime = getTime();
        if (endTime - startTime != 0)
        {
            fps = 1000 / (endTime - startTime);
        }
        else
        {
            fps = 1000;
        }
    }
}

int getTime()
{
    struct timespec time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time);
    return time.tv_sec * 1000 + time.tv_nsec / 1000000;
}

void renderMap(sf::RenderWindow& window, Map* map)
{
    for (int x = 0; x < 100; x++)
    {
        for (int y = 0; y < 100; y++)
        {
            if (map->getCell(x, y, 0).getType() == FloorCellType::Grass)
            {
                sf::RectangleShape shape(sf::Vector2f(10, 10));
                shape.setPosition(x * 10, y * 10);
                shape.setFillColor(sf::Color::Green);
                window.draw(shape);
            }
            else if (map->getCell(x, y, 0).getType() == FloorCellType::Stone)
            {
                sf::RectangleShape shape(sf::Vector2f(10, 10));
                shape.setPosition(x * 10, y * 10);
                shape.setFillColor(sf::Color(128, 128, 128));
                window.draw(shape);
            }
        }
    }
}