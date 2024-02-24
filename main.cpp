#include <SFML/Graphics.hpp>
#include "InternalServer/Position/Coordinates.hpp"
#include "InternalServer/Position/Vector2d.cpp"
#include "InternalServer/Map/Layout.hpp"
#include "Camera.hpp"
#include "InternalServer/ObjOnLayout/ObjOnLayout.cpp"
#include "InternalServer/Event/Event.hpp"
#include <random>
#include "InternalServer/ObjOnLayout/Debug/DebugObj.hpp"
#include "Debug/FpsCounter.hpp"
#include "InternalServer/ObjOnLayout/Unit/Unit.hpp"
#include "InternalServer/ObjOnLayout/Unit/GameCharacter/NPC.hpp"
#include <list>
#include <iostream>

int main()
{
    const int windowWidth = 800;
    const int windowHeight = 600;
    Layout layout;

    Unit player(Coordinates(9, 9), Vector2d(0.8, 0.8), layout);
    player.setSpeed(0.5);

    std::list<NPC*> list;

    for (int i = 0; i < 1000; i++)
    {
        list.push_back(new NPC(Coordinates(rand() % 20 + 30, rand() % 20 + 30), Vector2d(0.8, 0.8), layout));
        std::cout << "x: " << list.back()->getPos().x << " y: " << list.back()->getPos().y << std::endl;
        list.back()->setSpeed((rand() % 20 + 1) / 100.0);
    }
    

    // NPC npc(Coordinates(1, 10), Vector2d(1, 1), layout);
    
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

        int x = 0;
        int y = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) y++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) x--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) y--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) x++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) x++,y--;

        if (x != 0 or y != 0)
        {
            player.move(atan2(y, x) * 180 / M_PI);
        }

        // npc.walk(player.getPos());

        for (auto i : list) i->walk(player.getPos());

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