#include <SFML/Graphics.hpp>
#include "InternalServer/Map/Layout.hpp"
#include "Camera.hpp"
#include "InternalServer/ObjOnLayout/ObjOnLayout.cpp"
#include "InternalServer/Event/Event.hpp"
#include <random>
#include "InternalServer/ObjOnLayout/Debug/DebugObj.hpp"
#include "Debug/FpsCounter.hpp"

int main()
{
    const int windowWidth = 800;
    const int windowHeight = 600;
    Layout layout;

    ObjOnLayout player(Coordinates(20, 30), Vector2d(1, 1), layout);

    ObjOnLayout debugObj(Coordinates(10, 10), Vector2d(1, 1), layout);

    for (int i = 0; i < 5; i++)
    {
        new ObjOnLayout(Coordinates(rand() % 100, rand() % 100), Vector2d(1, 0.5), layout);
    }
    
    Camera camera(player, layout, 21, windowWidth, windowHeight);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML window");

    window.setFramerateLimit(60);

    int startTime = 0;
    int endTime = 1;
    int fps = 0;

    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");

    FpsCounter fpsCounter(font);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseWheelScrolled and event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                if (event.mouseWheelScroll.delta > 0)
                {
                    camera.setScale(camera.getScale() * 1.1);
                }
                else
                {
                    camera.setScale(camera.getScale() * 0.9);
                }
            }
        }

        fpsCounter.getStartTime();

        layout.tick();

        window.clear();
        
        camera.render(window);

        sf::RectangleShape rect(sf::Vector2f(1, 1));
        rect.setPosition(windowWidth / 2, windowHeight / 2);
        rect.setFillColor(sf::Color::Red);
        window.draw(rect);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) player.setPos(player.getPos() + Coordinates(0, -0.3));+
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) player.setPos(player.getPos() + Coordinates(0, 0.3));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player.setPos(player.getPos() + Coordinates(-0.3, 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player.setPos(player.getPos() + Coordinates(0.3, 0));

        fpsCounter.getEndTime();
        
        fpsCounter.draw(window, windowWidth);

        window.display();

    }
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