#ifndef Camera_hpp_
#define Camera_hpp_
#include <SFML/Graphics.hpp>
#include "InternalServer/ObjOnLayout/ObjOnLayout.hpp"
#include "InternalServer/Map/Layout.hpp"
#include "InternalServer/Coordinates.hpp"
#include <list>

class Camera
{
private:
    Coordinates pos;
    ObjOnLayout* followObj;
    Layout* layout;
    sf::Texture mapTexture;
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
    sf::Texture texture;
    texture.create(100 * 16, 100 * 16);
    sf::Image image;
    image.create(100 * 16, 100 * 16, sf::Color::Black);
    for (int x = 0; x < 100 * 16; x++)
    {
        for (int y = 0; y < 100 * 16; y++)
        {
            if (layout->getMap()->getCell(x / 16, y / 16, 0)->getType() == MapCell::Type::Grass)
            {
                image.setPixel(x, y, sf::Color::Green);
            }
            else
            {
                image.setPixel(x, y, sf::Color(128, 128, 128));
            }
        }
    }
    texture.update(image);
    mapTexture = texture;
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
    pos.x = followObj->getPos().x + followObj->getSize().x / 2;
    pos.y = followObj->getPos().y + followObj->getSize().y / 2;

    sf::Sprite sprite;
    sprite.setTexture(mapTexture);
    sprite.setPosition(-pos.x * scale + windowWidth / 2, -pos.y * scale + windowHeight / 2);
    sprite.setScale(scale / 16, scale / 16);
    window.draw(sprite);

    for (int x = 0; x < 100; x++)
    {
        for (int y = 0; y < 100; y++)
        {
            for (auto i : *layout->getMap()->getCell(x, y, 0)->getObjects())
            {
                sf::RectangleShape rect(sf::Vector2f(i->getSize().x * scale, i->getSize().y * scale));
                rect.setPosition((i->getPos().x - pos.x) * scale + windowWidth / 2, (i->getPos().y - pos.y) * scale + windowHeight / 2);
                rect.setFillColor(sf::Color::Red);
                window.draw(rect);
            }
        }
    }
    // double speed = sqrt(followObj->getPos().x - pos.x) / 100;
    // double speed = 1 - (1 / (sqrt((followObj->getPos().x - pos.x) * (followObj->getPos().x - pos.x) + (followObj->getPos().y- pos.y) * (followObj->getPos().y- pos.y)) + 1));
    // pos.x += (followObj->getPos().x - pos.x) * speed / scale;
    // pos.y += (followObj->getPos().y - pos.y) * speed / scale;

}

Camera::~Camera()
{
}

#endif