#ifndef HUD_hpp_
#define HUD_hpp_
#include <SFML/Graphics.hpp>

class HUD
{
private:
    sf::RenderWindow* window;
    bool isOpen = true;
    int windowWidth;
    int windowHeight;
public:
    HUD(sf::RenderWindow& window, int windowWidth, int windowHeight);
    void draw();
    void close();
    void open();
    void change();
    ~HUD();
};

HUD::HUD(sf::RenderWindow& window, int windowWidth, int windowHeight) : windowWidth(windowWidth), windowHeight(windowHeight) { this->window = &window; }

void HUD::draw()
{
    if (isOpen)
    {
        sf::RectangleShape rect(sf::Vector2f(1000, 100));
        rect.setPosition(windowWidth / 2 - 500, windowHeight - 100);
        rect.setFillColor(sf::Color::Black);
        window->draw(rect);
    }
}

void HUD::close() { isOpen = false; }
void HUD::open() { isOpen = true; }
void HUD::change() { isOpen = !isOpen; }

HUD::~HUD()
{
}


#endif