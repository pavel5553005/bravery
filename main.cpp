#include <SFML/Graphics.hpp>
#include "InternalServer/Map/Layout.hpp"
#include "Camera.hpp"
#include "InternalServer/ObjOnLayout/ObjOnLayout.cpp"
#include "InternalServer/Event/EventHandler.hpp"
#include <random>
#include "InternalServer/ObjOnLayout/Debug/DebugObj.hpp"
#include "Debug/FpsCounter.hpp"

void drawTextLeft(sf::RenderWindow& window, sf::Font& font, std::string text, int index);

int main()
{
    EventHandler eventHandler;

    const int windowWidth = 800;
    const int windowHeight = 600;
    Layout layout(&eventHandler);

    ObjOnLayout player(Coordinates(20, 30), Vector2d(10, 1), &layout);

    // ObjOnLayout* player2 = new ObjOnLayout(Coordinates(30, 40), Vector2d(0.5, 0.5), &layout);

    // ObjOnLayout objects[100];

    for (int i = 0; i < 500; i++)
    {
        new DebugObj(Coordinates(rand() % 100, rand() % 100), Vector2d(0.5, 0.5), &layout, &player);
    }
    
    Camera camera(&player, &layout, 21, windowWidth, windowHeight);

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

        layout.tick();

        window.clear();

        fpsCounter.getStartTime();
        
        camera.render(window);


        drawTextLeft(window, font, "Count: " + std::to_string(layout.getObjects()->size()), 0);
        drawTextLeft(window, font, "xPos: " + std::to_string(camera.getPos().x), 1);
        drawTextLeft(window, font, "yPos: " + std::to_string(camera.getPos().y), 2);
        drawTextLeft(window, font, "0x0y: " + std::to_string(layout.getMap()->getCell(0, 0, 0)->getObjects()->size()), 3);

        sf::RectangleShape rect(sf::Vector2f(1, 1));
        rect.setPosition(windowWidth / 2, windowHeight / 2);
        rect.setFillColor(sf::Color::Red);
        window.draw(rect);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) player.move(Coordinates(0, -0.3));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) player.move(Coordinates(0, 0.3));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) player.move(Coordinates(-0.3, 0));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) player.move(Coordinates(0.3, 0));


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