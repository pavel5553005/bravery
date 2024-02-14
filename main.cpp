#include <SFML/Graphics.hpp>

int getTime();
int main()
{

    const int windowWidth = 800;
    const int windowHeight = 600;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "SFML window");

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