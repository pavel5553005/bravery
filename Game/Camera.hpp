#ifndef Camera_hpp_
#define Camera_hpp_

#define TILE_SIZE 32
#include <SFML/Graphics.hpp>
#include "../InternalServer/ObjOnLayout/ObjOnLayout.hpp"
#include "../InternalServer/Map/Layout.hpp"
#include "../InternalServer/Position/Coordinates.hpp"
#include "../Resources/ResourceManager.hpp"
#include "MapTextureGenerator.hpp"
#include <list>

class Camera
{
private:
    Coordinates pos;
    ObjOnLayout* followObj;
    sf::Texture* floorTexture;
    sf::Texture* wallsTexture;
    sf::RectangleShape backgroundSprite;

    sf::Image grassImage;
    sf::Image stoneImage;

    double scale;
public:
    Camera() { }
    Camera(ObjOnLayout& followObj, const double scale);

    const Coordinates getPos();
    double getScale();

    void setScale(double scale);

    void render();
    void generateTextures();
    
    ~Camera();
};

Camera::Camera(ObjOnLayout& followObj, const double scale) : 
followObj(&followObj), scale(scale) { }

const Coordinates Camera::getPos()
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

    // double speed = (1 - (1 / (sqrt((followObj->getPos().x - pos.x) * (followObj->getPos().x - pos.x) + (followObj->getPos().y- pos.y) * (followObj->getPos().y- pos.y)) + 1))) / scale * 10;
    // // if (speed <= scale / 100)
    // // {
    // //     pos.x = followObj->getPos().x + followObj->getSize().x / 2;
    // //     pos.y = followObj->getPos().y + followObj->getSize().y / 2;
    // // }
    // // else
    // // {
    // BaS.console.log("speed: " + std::to_string(scale));
    // pos.x += (followObj->getPos().x - pos.x + followObj->getSize().x / 2) * speed * scale / 100;
    // pos.y += (followObj->getPos().y - pos.y + followObj->getSize().y / 2) * speed * scale / 100;
    // }

    BaS.window.draw(backgroundSprite);

    sf::Sprite floorSprite;
    floorSprite.setTexture(floorTexture[followObj->getPos().z]);
    floorSprite.setPosition(-pos.x * scale + BaS.windowWidth / 2, -pos.y * scale + BaS.windowHeight / 2);
    floorSprite.setScale(scale / TILE_SIZE, scale / TILE_SIZE);
    BaS.window.draw(floorSprite);

    for (auto i : followObj->getLayout().getObjects())
    {
        if (i->getPos().z != followObj->getPos().z) continue;
        // if (i != followObj)
        // {
        //     sf::RectangleShape rect(sf::Vector2f(i->getSize().x * scale, i->getSize().y * scale));
        //     rect.setPosition((i->getPos().x - pos.x) * scale + BaS.windowWidth / 2, (i->getPos().y - pos.y) * scale + BaS.windowHeight / 2);
        //     rect.setFillColor(sf::Color::Blue);
        //     BaS.window.draw(rect);
        // }
        // else
        // {
        //     sf::RectangleShape rect(sf::Vector2f(i->getSize().x * scale, i->getSize().y * scale));
        //     rect.setPosition((i->getPos().x - pos.x) * scale + BaS.windowWidth / 2, (i->getPos().y - pos.y) * scale + BaS.windowHeight / 2);
        //     rect.setFillColor(sf::Color::Red);
        //     BaS.window.draw(rect);
        // }
        sf::Sprite sprite;
        sprite.setTexture(i->getTexture().getTexture());
        sprite.setPosition((i->getPos().x - pos.x) * scale + BaS.windowWidth / 2, (i->getPos().y - pos.y) * scale + BaS.windowHeight / 2);
        sprite.setScale(scale / TILE_SIZE * 2, scale / TILE_SIZE * 2);
        BaS.window.draw(sprite);
    }

    // for (int y = 0; y < 100; y++)
    // {
    //     for (int x = 0; x < 100; x++)
    //     {
    //         for (auto i : *followObj->getLayout()->getMap()->getCell(x, y, 0)->getObjects())
    //         {
    //             if (i != followObj)
    //             {
    //                 sf::RectangleShape rect(sf::Vector2f(i->getSize().x * scale, i->getSize().y * scale));
    //                 rect.setPosition((i->getPos().x - pos.x) * scale + BaS.windowWidth / 2, (i->getPos().y - pos.y) * scale + BaS.windowHeight / 2);
    //                 rect.setFillColor(sf::Color::Blue);
    //                 BaS.window.draw(rect);
    //             }
    //             else
    //             {
    //                 sf::RectangleShape rect(sf::Vector2f(i->getSize().x * scale, i->getSize().y * scale));
    //                 rect.setPosition((i->getPos().x - pos.x) * scale + BaS.windowWidth / 2, (i->getPos().y - pos.y) * scale + BaS.windowHeight / 2);
    //                 rect.setFillColor(sf::Color::Red);
    //                 BaS.window.draw(rect);
    //             }
    //         }
    //     }
    // }
        
    sf::Sprite wallsSprite;
    wallsSprite.setTexture(wallsTexture[followObj->getPos().z]);
    wallsSprite.setPosition(-pos.x * scale + BaS.windowWidth / 2, -pos.y * scale + BaS.windowHeight / 2);
    wallsSprite.setScale(scale / 16, scale / 16);
    BaS.window.draw(wallsSprite);
}

void Camera::generateTextures()
{

    floorTexture = new sf::Texture[followObj->getLayout().getMap().getSizeZ()];
    wallsTexture = new sf::Texture[followObj->getLayout().getMap().getSizeZ()];

    MapTextureGenerator::MapTexture mapTexture = MapTextureGenerator::generateMapTexture(followObj->getLayout().getMap());
    int index = 0;
    for (auto i : mapTexture.floorTexture)
    {
        floorTexture[index].loadFromImage(i);
        index++;
    }

    index = 0;
    for (auto i : mapTexture.wallTexture)
    {
        wallsTexture[index].loadFromImage(i);
        index++;
    }

    backgroundSprite.setSize(sf::Vector2f(BaS.windowWidth, BaS.windowHeight));
    backgroundSprite.setPosition(0, 0);
    backgroundSprite.setFillColor(sf::Color(85, 85, 85));
}

Camera::~Camera()
{
}

#endif