#ifndef Camera_hpp_
#define Camera_hpp_
#include <SFML/Graphics.hpp>
#include "ObjOnLayout/ObjOnLayout.hpp"
#include "Map/Layout.hpp"
#include "Coordinates.hpp"

class Camera
{
private:
    Coordinates pos;
    ObjOnLayout* followObj;
    Layout* layout;
    int scale;
public:
    Camera();
    Camera(ObjOnLayout* followObj, Layout* layout, int scale);
    Coordinates getPos();
    void render(sf::RenderWindow& window);
    ~Camera();
};

Camera::Camera(ObjOnLayout* followObj, Layout* layout, int scale)
{
    this->followObj = followObj;
    this->pos = followObj->getPos();
    this->scale = scale;
    this->layout = layout;
}

Camera::Camera()
{
}

Coordinates Camera::getPos()
{
    return pos;
}

void Camera::render(sf::RenderWindow& window)
{
    for (int x = 0; x < 100; x++)
    {
        for (int y = 0; y < 100; y++)
        {
            if (layout->getMap()->getCell(x, y, 0).getType() == Grass)
            {
                sf::RectangleShape rect(sf::Vector2f(scale, scale));
                rect.setPosition((x - pos.x) * scale, (y - pos.y) * scale);
                rect.setFillColor(sf::Color::Green);
                window.draw(rect);
            }                                    
            else if (layout->getMap()->getCell(x, y, 0).getType() == Stone)
            {
                sf::RectangleShape rect(sf::Vector2f(scale, scale));
                rect.setPosition((x - pos.x) * scale, (y - pos.y) * scale);
                rect.setFillColor(sf::Color(128, 128, 128));
                window.draw(rect);
            }
        }
    }
    // double speed = sqrt(followObj->getPos().x - pos.x) / 100;
    double speed = 0.02 - (0.02 / (sqrt((followObj->getPos().x - pos.x) * (followObj->getPos().x - pos.x) + (followObj->getPos().y- pos.y) * (followObj->getPos().y- pos.y)) + 1));
    pos.x += (followObj->getPos().x - pos.x) * speed;
    pos.y += (followObj->getPos().y - pos.y) * speed;

}

Camera::~Camera()
{
}

#endif