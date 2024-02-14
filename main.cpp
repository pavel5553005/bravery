#include <SFML/Graphics.hpp>
#include "Map/Layout.hpp"
#include "Camera.hpp"
#include "ObjOnLayout/ObjOnLayout.cpp"

int getTime();

int main()
{

    Layout layout;

    Coordinates pos;
    pos.x = 0;
    pos.y = 0;
    pos.z = 0;

    ObjOnLayout player (pos, Vector2d(10, 10), &layout);

    Camera camera(&player, &layout, 20);

    const int windowWidth = 800;
    const int windowHeight = 600;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML window");

    window.setFramerateLimit(60);

    int startTime = 0;
    int endTime = 1;
    int fps = 0;
    
    int scet = 0;

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
        
        camera.render(window);

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

        sf::Text xPos;
        xPos.setFont(font);
        xPos.setString(std::to_string(camera.getPos().x));
        xPos.setCharacterSize(10);
        xPos.setFillColor(sf::Color::Black);
        xPos.setPosition(0, 0);
        window.draw(xPos);

        sf::Text yPos;
        yPos.setFont(font);
        yPos.setString(std::to_string(camera.getPos().y));
        yPos.setCharacterSize(10);
        yPos.setFillColor(sf::Color::Black);
        yPos.setPosition(0, 10);
        window.draw(yPos);

        sf::RectangleShape playerShape;
        playerShape.setSize(sf::Vector2f(10, 10));
        playerShape.setPosition((player.getPos().x - camera.getPos().x + 20) * 20, (player.getPos().y - camera.getPos().y + 20) * 20);
        playerShape.setFillColor(sf::Color::Red);
        window.draw(playerShape);



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) pos.y -= 0.3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) pos.y += 0.3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) pos.x -= 0.3;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) pos.x += 0.3;

        player.setPos(pos);

        window.display();

        scet++;



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