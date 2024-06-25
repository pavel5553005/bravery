#ifndef FpsCounter_hpp_
#define FpsCounter_hpp_
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include <random>

class FpsCounter
{
private:
    std::list<int> points;
    sf::Texture texture;
    int startTime;
    int endTime;
    int cointer;
    int fps;
    int fpsCounter;
    int averageFps;
    sf::Font font;
    int getTime();
    sf::Color getColor(int index);
public:
    FpsCounter(sf::Font& font);
    void getStartTime();
    void getEndTime();
    void draw(sf::RenderWindow& window);
    void drawTextLeft(sf::RenderWindow& window, std::string text);
};

FpsCounter::FpsCounter(sf::Font& font)
{
    this->font = font;
    texture.create(100, 40);
    sf::Image image;
    image.create(100, 40, sf::Color::Black);
    texture.update(image);
    averageFps = 0;
    cointer = 0;
    fpsCounter = 0;
}

int FpsCounter::getTime()
{
    struct timespec time;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time);
    return time.tv_sec * 1000 + time.tv_nsec / 1000000;
}

void FpsCounter::getStartTime()
{
    startTime = getTime();
}

void FpsCounter::getEndTime()
{
    endTime = getTime();
    if (endTime - startTime == 0)
    {
        fps = 1000;
    }
    else
    {
        fps = 1000 / (endTime - startTime);
    }
    cointer++;
    fpsCounter += fps;
    if (cointer == 20)
    {
        points.push_back(fpsCounter / 20);
        averageFps = (fpsCounter / 20);
        fpsCounter = 0;
        cointer = 0;
        if (points.size() > 100)
        {
            points.pop_front();
        }
    }
}

sf::Color FpsCounter::getColor(int index)
{
    if (index != 0)
    {
        return sf::Color(255 / index, index / 4, 0);
    }
    return sf::Color(255, 0, 0);
    
}

void FpsCounter::draw(sf::RenderWindow& window)
{
    try
    {
        sf::Image image;
        image.create(100, 40, sf::Color::Black);
        int j = 0;
        if (cointer == 0)       
        {
            for (auto i : points)
            {
                if (i == 0) i = 1;
                for (int k = 39; k > (1000 - i) / 25; k--)
                {
                    image.setPixel(j, k, sf::Color::White);
                }
                
                j++;
            }
            texture.update(image);
        }
        
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setPosition(WINDOW_WIDTH - 100, 0);
        window.draw(sprite);

        sf::RectangleShape rect(sf::Vector2f(std::to_string(averageFps).length() * 11, 20));
        rect.setPosition(WINDOW_WIDTH - std::to_string(averageFps).length() * 11, 40);
        rect.setFillColor(sf::Color::Black);
        window.draw(rect);

        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(16);
        text.setString(std::to_string(averageFps));
        text.setFillColor(sf::Color::White);
        text.setPosition(WINDOW_WIDTH - std::to_string(averageFps).length() * 11, 40);
        window.draw(text);
    }
    catch(...)
    {
        std::cout << "Exception occurred: " << std::endl;
    }
}

#endif