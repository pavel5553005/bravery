#ifndef Camera_hpp_
#define Camera_hpp_
#include <SFML/Graphics.hpp>
#include "InternalServer/ObjOnLayout/ObjOnLayout.hpp"
#include "InternalServer/Map/Layout.hpp"
#include "InternalServer/Position/Coordinates.hpp"
#include "Resources/ResourceManager.hpp"
#include <list>

class Camera
{
private:
    Coordinates pos;
    ObjOnLayout* followObj;
    Layout* layout;
    sf::Texture* floorTexture;
    sf::Texture* wallsTexture;
    sf::RenderWindow* window;
    std::list<sf::RectangleShape> rectangleShapes;
    sf::RectangleShape backgroundSprite;

    sf::Image grassImage;
    sf::Image stoneImage;

    double scale;
    int windowHeight;
    int windowWidth;

    void generateWallTexture();
public:
    Camera();
    Camera(ObjOnLayout& followObj, Layout& layout, double scale, sf::RenderWindow& window, int windowWidth, int windowHeight);

    Coordinates getPos();
    double getScale();

    void setScale(double scale);

    void render();
    void drawRectangle(sf::Color color, Coordinates pos, Vector2d size);
    
    ~Camera();
};

Camera::Camera(ObjOnLayout& followObj, Layout& layout, double scale, sf::RenderWindow& window, int windowWidth, int windowHeight)
{
    this->followObj = &followObj;
    this->pos = followObj.getPos();
    this->scale = scale;
    this->layout = &layout;
    this->window = &window;
    this->windowHeight = windowHeight;
    this->windowWidth = windowWidth;

    grassImage.loadFromFile("Resources/Textures/Floor/GrassTexture.png");
    stoneImage.loadFromFile("Resources/Textures/Floor/StoneTexture.png");

    sf::Image floorImage;
    floorImage.create(layout.getMap()->getSizeX() * 16, layout.getMap()->getSizeY() * 16, sf::Color(255, 0, 255));
    floorTexture = new sf::Texture[layout.getMap()->getSizeZ()];
    for (int z = 0; z < layout.getMap()->getSizeZ(); z++)
    {
        floorTexture[z].create(layout.getMap()->getSizeX() * 16, layout.getMap()->getSizeY() * 16);
        for (int x = 0; x < layout.getMap()->getSizeX(); x++)
        {
            for (int y = 0; y < layout.getMap()->getSizeY(); y++)
            {
                if (layout.getMap()->getCell(x, y, z)->getFloorType() == MapCell::FloorType::Grass)
                {
                    floorImage.copy(grassImage, x * 16, y * 16, sf::IntRect(0, 0, 16, 16));
                }
                else if (layout.getMap()->getCell(x, y, z)->getFloorType() == MapCell::FloorType::Stone)
                {
                    floorImage.copy(stoneImage, x * 16, y * 16, sf::IntRect(0, 0, 16, 16));
                }
            }
        }
        floorTexture[z].update(floorImage);
    }

    backgroundSprite.setSize(sf::Vector2f(windowWidth, windowHeight));
    backgroundSprite.setPosition(0, 0);
    backgroundSprite.setFillColor(sf::Color(85, 85, 85));
    generateWallTexture();
}

Camera::Camera()
{
}

void Camera::generateWallTexture()
{
    wallsTexture = new sf::Texture[layout->getMap()->getSizeZ()];
    sf::Image wallImage;
    wallImage.create(layout->getMap()->getSizeX() * 16, layout->getMap()->getSizeY() * 16, sf::Color(0, 0, 0, 0));
    for (int z = 0; z < layout->getMap()->getSizeZ(); z++)
    {
        wallImage.create(layout->getMap()->getSizeX() * 16, layout->getMap()->getSizeY() * 16, sf::Color(0, 0, 0, 0));
        for (int x = 0; x < layout->getMap()->getSizeX(); x++)
        {
            for (int y = 0; y < layout->getMap()->getSizeY(); y++)
            {
                if (layout->getMap()->getCell(x, y, z)->getWallType() == MapCell::WallType::Wall)
                {
                    bool isTop = false;
                    bool isBottom = false;
                    bool isLeft = false;
                    bool isRight = false;
                    if (y > 0 and layout->getMap()->getCell(x, y - 1, z)->getWallType() != MapCell::WallType::None) isTop = true;
                    if (y < layout->getMap()->getSizeY() - 1 and layout->getMap()->getCell(x, y + 1, z)->getWallType() != MapCell::WallType::None) isBottom = true;
                    if (x > 0 and layout->getMap()->getCell(x - 1, y, z)->getWallType() != MapCell::WallType::None) isLeft = true;
                    if (x < layout->getMap()->getSizeX() - 1 and layout->getMap()->getCell(x + 1, y, z)->getWallType() != MapCell::WallType::None) isRight = true;
                    wallImage.copy(*resourceManager.getWallTexture(isTop, isBottom, isLeft, isRight), x * 16, y * 16, sf::IntRect(0, 0, 16, 16));
                }
            }
        }
        wallsTexture[z].loadFromImage(wallImage);
    }
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

void Camera::render()
{
    pos.x = followObj->getPos().x + followObj->getSize().x / 2;
    pos.y = followObj->getPos().y + followObj->getSize().y / 2;

    // double speed = 1 - (1 / (sqrt((followObj->getPos().x - pos.x) * (followObj->getPos().x - pos.x) + (followObj->getPos().y- pos.y) * (followObj->getPos().y- pos.y)) + 1));
    // pos.x += (followObj->getPos().x - pos.x + followObj->getSize().x / 2) * speed * scale / 100;
    // pos.y += (followObj->getPos().y - pos.y + followObj->getSize().y / 2) * speed * scale / 100;

    window->draw(backgroundSprite);

    sf::Sprite floorSprite;
    floorSprite.setTexture(floorTexture[followObj->getPos().z]);
    floorSprite.setPosition(-pos.x * scale + windowWidth / 2, -pos.y * scale + windowHeight / 2);
    floorSprite.setScale(scale / 16, scale / 16);
    window->draw(floorSprite);

    for (auto i : *layout->getObjects())
    {
        if (i != followObj)
        {
            sf::RectangleShape rect(sf::Vector2f(i->getSize().x * scale, i->getSize().y * scale));
            rect.setPosition((i->getPos().x - pos.x) * scale + windowWidth / 2, (i->getPos().y - pos.y) * scale + windowHeight / 2);
            rect.setFillColor(sf::Color::Blue);
            window->draw(rect);
        }
        else
        {
            sf::RectangleShape rect(sf::Vector2f(i->getSize().x * scale, i->getSize().y * scale));
            rect.setPosition((i->getPos().x - pos.x) * scale + windowWidth / 2, (i->getPos().y - pos.y) * scale + windowHeight / 2);
            rect.setFillColor(sf::Color::Red);
            window->draw(rect);
        }
    }

    // for (int y = 0; y < 100; y++)
    // {
    //     for (int x = 0; x < 100; x++)
    //     {
    //         for (auto i : *layout->getMap()->getCell(x, y, 0)->getObjects())
    //         {
    //             if (i != followObj)
    //             {
    //                 sf::RectangleShape rect(sf::Vector2f(i->getSize().x * scale, i->getSize().y * scale));
    //                 rect.setPosition((i->getPos().x - pos.x) * scale + windowWidth / 2, (i->getPos().y - pos.y) * scale + windowHeight / 2);
    //                 rect.setFillColor(sf::Color::Blue);
    //                 window->draw(rect);
    //             }
    //             else
    //             {
    //                 sf::RectangleShape rect(sf::Vector2f(i->getSize().x * scale, i->getSize().y * scale));
    //                 rect.setPosition((i->getPos().x - pos.x) * scale + windowWidth / 2, (i->getPos().y - pos.y) * scale + windowHeight / 2);
    //                 rect.setFillColor(sf::Color::Red);
    //                 window->draw(rect);
    //             }
    //         }
    //     }
    // }
        
    sf::Sprite wallsSprite;
    wallsSprite.setTexture(wallsTexture[followObj->getPos().z]);
    wallsSprite.setPosition(-pos.x * scale + windowWidth / 2, -pos.y * scale + windowHeight / 2);
    wallsSprite.setScale(scale / 16, scale / 16);
    window->draw(wallsSprite);

    for ( auto i : rectangleShapes)
    {
        window->draw(i);
    }

    rectangleShapes.clear();
}

void Camera::drawRectangle(sf::Color color, Coordinates pos, Vector2d size)
{
    sf::RectangleShape rect(sf::Vector2f(size.x * scale, size.y * scale));
    rect.setPosition((pos.x - this->pos.x) * scale + windowWidth / 2, (pos.y - this->pos.y) * scale + windowHeight / 2);
    rect.setFillColor(color);
    rectangleShapes.push_back(rect);
}

Camera::~Camera()
{
}

#endif