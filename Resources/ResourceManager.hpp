#ifndef RESOURCEMANAGER_HPP_
#define RESOURCEMANAGER_HPP_

#include <SFML/Graphics.hpp>
#include "../InternalServer/Map/Map.hpp"
#include "../InternalServer/Map/MapCell.hpp"
#include "../InternalServer/AnimatedTexture.hpp"
#include "../InternalServer/AnimatedTexture.hpp"
#include "CvsReader.hpp"
#include <vector>
#include <list>

class ResourceManager
{
private:
    struct TextureContainer
    {
        int users;
        std::string path;
        std::vector<sf::Texture>* textures;
        TextureContainer(std::vector<sf::Texture>* t) : textures(t) { users = 0; }
        bool operator == (const TextureContainer& other) { return path == other.path; }
    };
    sf::Image wallTextures[4][4];
    std::list<TextureContainer*> textures;
    
public:
    ResourceManager();

    sf::Image* getWallTexture(bool isTop, bool isBottom, bool isLeft, bool isRight);

    AnimatedTexture loadAnimatedTexture(std::string path);
    void deleteAnimatedTexture(AnimatedTexture& texture);

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

AnimatedTexture ResourceManager::loadAnimatedTexture(std::string path)
{
    for (auto i : textures)
    {
        if (i->path == path)
        {
            i->users++;
            return AnimatedTexture(i->textures);
        }
    }
    TextureContainer* t = new TextureContainer(getTextureFromCsv(path));
    t->path = path;
    t->users++;
    textures.push_back(t);
    return AnimatedTexture(t->textures);
}

void ResourceManager::deleteAnimatedTexture(AnimatedTexture& texture)
{
    for (auto i : textures)
    {
        if (texture == i->textures)
        {
            i->users--;
            if (i->users == 0)
            {
                textures.remove(i);
                delete i;
            }
            return;
        }
    }
}

ResourceManager::~ResourceManager()
{
}

ResourceManager resourceManager;


#endif