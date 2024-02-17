#include <SFML/Graphics.hpp>
#include "InternalServer/Map/Layout.hpp"
#include "Camera.hpp"
#include "InternalServer/ObjOnLayout/ObjOnLayout.cpp"
#include "InternalServer/Event/EventHandler.hpp"

int getTime();

void drawTextLeft(sf::RenderWindow& window, sf::Font& font, std::string text, int index);

int main()
{
    EventHandler eventHandler;

    const int windowWidth = 800;
    const int windowHeight = 600;
    Layout layout(&eventHandler);

    ObjOnLayout player(Coordinates(20, 30), Vector2d(0.5, 0.5), &layout);

    Coordinates position = player.getPos();

    std::list<ObjOnLayout> objects;

    for (int i = 0; i < 100; i++)
    {
        objects.push_back(ObjOnLayout(Coordinates(i, i), Vector2d(0.5, 0.5), &layout));
    }
    

    Camera camera(&player, &layout, 21, windowWidth, windowHeight);

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
        
        camera.render(window);

        drawTextLeft(window, font, "Count: " + std::to_string(layout.getObjects().size()), 0);

        drawTextLeft(window, font, "xPos: " + std::to_string(camera.getPos().x), 1);

        drawTextLeft(window, font, "yPos: " + std::to_string(camera.getPos().y), 2);

        // drawTextLeft(window, font, "y: " + std::to_string(arr[0].getPos().y), 3);

        // drawTextLeft(window, font, "x: " + std::to_string(arr[0].getPos().x), 4);

        sf::RectangleShape rect(sf::Vector2f(1, 1));
        rect.setPosition(windowWidth / 2, windowHeight / 2);
        rect.setFillColor(sf::Color::Red);
        window.draw(rect);


        sf::Text fpsText;
        fpsText.setFont(font);
        fpsText.setString(std::to_string(fps));
        fpsText.setCharacterSize(10);
        fpsText.setFillColor(sf::Color::Green);
        fpsText.setPosition(windowWidth - 30, 0);
        window.draw(fpsText);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) position.y -= 0.3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) position.y += 0.3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) position.x -= 0.3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) position.x += 0.3;

        player.setPos(position);

        endTime = getTime();
        if (endTime - startTime != 0)
        {
            fps = 1000 / (endTime - startTime);
        }
        else
        {
            fps = 1000;
        }
        
        window.display();
    }
}

int getTime()
{
    struct timespec time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time);
    return time.tv_sec * 1000 + time.tv_nsec / 1000000;
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