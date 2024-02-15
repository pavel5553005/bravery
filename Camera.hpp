#ifndef Camera_hpp_
#define Camera_hpp_
#include <SFML/Graphics.hpp>
#include "InternalServer/ObjOnLayout/ObjOnLayout.hpp"
#include "InternalServer/Map/Layout.hpp"
#include "InternalServer/Coordinates.hpp"

class Camera
{
private:
    Coordinates pos;
    ObjOnLayout* followObj;
    Layout* layout;
    double scale;
    int windowHeight;
    int windowWidth;
public:
    Camera();
    Camera(ObjOnLayout* followObj, Layout* layout, double scale, int windowWidth, int windowHeight);
    Coordinates getPos();
    double getScale();
    void setScale(double scale);
    void render(sf::RenderWindow& window);
    ~Camera();
};

Camera::Camera(ObjOnLayout* followObj, Layout* layout, double scale, int windowWidth, int windowHeight)
{
    this->followObj = followObj;
    this->pos = followObj->getPos();
    this->scale = scale;
    this->layout = layout;
    this->windowHeight = windowHeight;
    this->windowWidth = windowWidth;
}

Camera::Camera()
{
}

Coordinates Camera::getPos()
{
    return pos;
}

double Camera::getScale()
{
    return scale;
}

void Camera::setScale(double scale)
{
    if (scale < 200 and scale > 10)
    {
        this->scale = scale;
    }
}

void Camera::render(sf::RenderWindow& window)
{
    for (int x = 0; x < 100; x++)
    {
        for (int y = 0; y < 100; y++)
        {
            Coordinates screenPos;
            screenPos.x = (x - pos.x) * scale + windowWidth / 2;
            screenPos.y = (y - pos.y) * scale + windowHeight / 2;
            if (layout->getMap()->getCell(x, y, 0)->getObj() != nullptr)
            {
                sf::RectangleShape rect(sf::Vector2f(scale, scale));
                rect.setPosition(screenPos.x, screenPos.y);
                rect.setFillColor(sf::Color::Blue);
                window.draw(rect);
            }
            else if (layout->getMap()->getCell(x, y, 0)->getType() == Grass)
            {
                sf::RectangleShape rect(sf::Vector2f(scale, scale));
                rect.setPosition(screenPos.x, screenPos.y);
                rect.setFillColor(sf::Color::Green);
                window.draw(rect); 
                
            }                                    
            else if (layout->getMap()->getCell(x, y, 0)->getType() == Stone)
            {
                sf::RectangleShape rect(sf::Vector2f(scale, scale));
                rect.setPosition(screenPos.x, screenPos.y);
                rect.setFillColor(sf::Color(128, 128, 128));
                window.draw(rect);
            }
        }
    }
    // double speed = sqrt(followObj->getPos().x - pos.x) / 100;
    // double speed = 1 - (1 / (sqrt((followObj->getPos().x - pos.x) * (followObj->getPos().x - pos.x) + (followObj->getPos().y- pos.y) * (followObj->getPos().y- pos.y)) + 1));
    // pos.x += (followObj->getPos().x - pos.x) * speed / scale;
    // pos.y += (followObj->getPos().y - pos.y) * speed / scale;
    pos.x = followObj->getPos().x;
    pos.y = followObj->getPos().y;

}

Camera::~Camera()
{
}

#endif