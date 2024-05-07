#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

#include <SFML/Graphics.hpp>
#include "../InternalServer/Map/Map.hpp"
#include "../InternalServer/Map/MapCell.hpp"

class ResourceManager
{
private:
    sf::Image wallTextures[4][4];
public:
    ResourceManager();
    sf::Image* getWallTexture(bool isTop, bool isBottom, bool isLeft, bool isRight);
    ~ResourceManager();
};

ResourceManager::ResourceManager()
{
    sf::Image wallImage;
    wallImage.create(64, 64, sf::Color::White);
    wallImage.loadFromFile("Resources/Textures/Wall/TestWall.png");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            wallTextures[i][j].create(16, 16, sf::Color::Black);
            wallTextures[i][j].copy(wallImage, 0, 0, sf::IntRect(j * 16, i * 16, 16, 16));
        }
    }
}

sf::Image* ResourceManager::getWallTexture(bool isTop, bool isBottom, bool isLeft, bool isRight)
{
    int i = 0;
    int j = 0;
    if (isTop) i++;
    if (isBottom) i += 2;
    if (isLeft) j++;
    if (isRight) j += 2;
    return &wallTextures[j][i];
}

ResourceManager::~ResourceManager()
{
}

ResourceManager resourceManager;


#endif