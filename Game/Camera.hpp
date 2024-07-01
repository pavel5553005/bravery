#ifndef Camera_hpp_
#define Camera_hpp_

#define TILE_SIZE 32
#include <SFML/Graphics.hpp>
#include "../InternalServer/ObjOnLayout/ObjOnLayout.hpp"
#include "../InternalServer/ObjOnLayout/Unit/GameCharacter/GameCharacter.hpp"
#include "../InternalServer/ObjOnLayout/Unit/Unit.hpp"
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
        double ObjPosX = (i->getPos().x - pos.x) * scale + BaS.windowWidth / 2;
        double ObjPosY = (i->getPos().y - pos.y) * scale + BaS.windowHeight / 2;
        
        if (i->getPos().z != followObj->getPos().z) continue;
        sf::Sprite sprite;
        sprite.setTexture(i->getTexture().getTexture());
        sprite.setPosition(ObjPosX, ObjPosY);
        sprite.setScale(scale / TILE_SIZE * 2, scale / TILE_SIZE * 2);
        BaS.window.draw(sprite);
    }
        
    sf::Sprite wallsSprite;
    wallsSprite.setTexture(wallsTexture[followObj->getPos().z]);
    wallsSprite.setPosition(-pos.x * scale + BaS.windowWidth / 2, -pos.y * scale + BaS.windowHeight / 2);
    wallsSprite.setScale(scale / 16, scale / 16);
    BaS.window.draw(wallsSprite);

    for (auto i : followObj->getLayout().getObjects())
    {
        double ObjPosX = (i->getPos().x - pos.x) * scale + BaS.windowWidth / 2;
        double ObjPosY = (i->getPos().y - pos.y) * scale + BaS.windowHeight / 2;

        if (auto unit = dynamic_cast<Unit*>(i); unit)
        {
            sf::RectangleShape hpLine;
            hpLine.setFillColor(sf::Color::Green);
            hpLine.setSize(sf::Vector2f(1 * scale * unit->getHp() / unit->getMaxHp(), 0.1 * scale));
            hpLine.setOrigin(0.5 * scale, 0.05 * scale);
            hpLine.setPosition(ObjPosX + (i->getSize().x / 2) * scale, ObjPosY - 0.2 * scale);
            BaS.window.draw(hpLine);

            sf::RectangleShape hpBar;
            hpBar.setFillColor(sf::Color(0, 0, 0, 0));
            hpBar.setSize(sf::Vector2f(1 * scale, 0.1 * scale));
            hpBar.setOutlineColor(sf::Color::Black);
            hpBar.setOutlineThickness(1);
            hpBar.setOrigin(0.5 * scale, 0.05 * scale);
            hpBar.setPosition(ObjPosX + (i->getSize().x / 2) * scale, ObjPosY - 0.2 * scale);
            BaS.window.draw(hpBar);
        }
        if (auto character = dynamic_cast<GameCharacter*>(i); character)
        {
            sf::Text text;
            text.setFont(BaS.font);
            text.setString(character->getName());
            text.setCharacterSize(16);
            text.setFillColor(sf::Color::Black);
            text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height);
            text.setPosition(ObjPosX + (i->getSize().x / 2) * scale, ObjPosY - 0.4 * scale);
            BaS.window.draw(text);
        }

    }
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