#include <SFML/Graphics.hpp>
#include "Debug/Debuger.hpp"
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
#include "InternalServer/ObjOnLayout/Unit/Animal/Animal.hpp"
#include <list>
#include <iostream>

int main()
{
    const int windowWidth = 1920;
    const int windowHeight = 1080;
    Layout layout;

    Unit player(Coordinates(30, 30), Vector2d(0.8, 0.8), layout);
    player.setSpeed(0.1);

    NPC npc(Coordinates(30, 30), Vector2d(1, 1), layout);
    npc.setSpeed(0.05);

    // for (int i = 0; i < 100; i++)
    // {
    //     npc.addPath(Coordinates(rand() % 30 + 30, rand() % 30 + 30));
    // }
    
    Animal animal(Coordinates(30, 30), Vector2d(0.8, 0.8), layout);
    animal.setSpeed(0.1);

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Game", sf::Style::Fullscreen);

    Camera camera(player, layout, 21, window ,windowWidth, windowHeight);
    window.setFramerateLimit(60);

    int startTime = 0;
    int endTime = 1;
    int fps = 0;
    int timeBeforeSpawnNPC = rand() % 600;

    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf");

    FpsCounter fpsCounter(font);

    debuger.setWindow(&window);
    debuger.setFont(font);

    std::list<NPC*> npcList;

    sf::RectangleShape backgroundSprite;
    backgroundSprite.setSize(sf::Vector2f(windowWidth, windowHeight));
    backgroundSprite.setPosition(0, 0);
    backgroundSprite.setFillColor(sf::Color(85, 85, 85));

    // for (int i = 0; i < 100; i++)
    // {
    //     debuger.consoleLog(std::to_string(i));
    // }
    

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

        if (npcList.size() < 1000)
        {
            npcList.push_back(new NPC(Coordinates(rand() % 30 + 30, rand() % 30 + 30), Vector2d(1, 1), layout));
            npcList.back()->setSpeed((rand() % 49 + 1 )/ 1000.0);
            debuger.consoleLog("Count of NPC: " + std::to_string(npcList.size()));
        }

        layout.tick();

        window.clear();

        window.draw(backgroundSprite);

        camera.render();

        // debuger.drawRectangle(sf::Color(255, 0, 0), Coordinates(player.getPos().x + 2, player.getPos().y + 2), player.getSize());

        int x = 0;
        int y = 0;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) y++;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) x--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) y--;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) x++;
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) debuger.consoleLog("GGGGGGGGGGHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH");

        if (x != 0 or y != 0)
        {
            player.move(atan2(y, x) * 180 / M_PI);
        }

        npc.move(animal.getPos());

        for (auto i : npcList) i->move(animal.getPos());

        fpsCounter.getEndTime();
        
        fpsCounter.draw(window, windowWidth);

        debuger.drawConsole();

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