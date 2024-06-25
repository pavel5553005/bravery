#ifndef MAP_TEXTURE_GENERATOR_HPP_
#define MAP_TEXTURE_GENERATOR_HPP_

#include <SFML/Graphics.hpp>
#include "../InternalServer/Map/Map.hpp"
#include <list>
#include "../Resources/ResourceManager.hpp"
#include <iostream>

namespace MapTextureGenerator
{
    struct MapTexture
    {
        std::list<sf::Image> floorTexture;
        std::list<sf::Image> wallTexture;
    };

    MapTexture generateMapTexture(Map& map)
    {
        MapTexture mapTexture;
        sf::Image floorImage;
        floorImage.create(map.getSizeX() * TILE_SIZE, map.getSizeY() * TILE_SIZE, sf::Color::Black);
        sf::Image wallImage;
        wallImage.create(map.getSizeX() * 16, map.getSizeY() * 16, sf::Color(0, 0, 0, 0));

        sf::Image grassImage;
        sf::Image stoneImage;

        grassImage.loadFromFile("Resources/Textures/Floor/Elements/TALLGRASS.png");
        stoneImage.loadFromFile("Resources/Textures/Floor/Rocks/GRAYROCKS.png");

        for (int z = 0; z < map.getSizeZ(); z++)
        {
            for (int x = 0; x < map.getSizeX(); x++)
            {
                for (int y = 0; y < map.getSizeY(); y++)
                {
                    if (map.getCell(x, y, z).getFloorType() == MapCell::FloorType::Grass)
                    {
                        floorImage.copy(grassImage, x * TILE_SIZE, y * TILE_SIZE, sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
                    }
                    else if (map.getCell(x, y, z).getFloorType() == MapCell::FloorType::Stone)
                    {
                        floorImage.copy(stoneImage, x * TILE_SIZE, y * TILE_SIZE, sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
                    }

                    if (map.getCell(x, y, z).getWallType() == MapCell::WallType::Wall)
                    {
                        bool isTop = false;
                        bool isBottom = false;
                        bool isLeft = false;
                        bool isRight = false;
                        if (y > 0 and map.getCell(x, y - 1, z).getWallType() != MapCell::WallType::None) isTop = true;
                        if (y < map.getSizeY() - 1 and map.getCell(x, y + 1, z).getWallType() != MapCell::WallType::None) isBottom = true;
                        if (x > 0 and map.getCell(x - 1, y, z).getWallType() != MapCell::WallType::None) isLeft = true;
                        if (x < map.getSizeX() - 1 and map.getCell(x + 1, y, z).getWallType() != MapCell::WallType::None) isRight = true;
                        wallImage.copy(*resourceManager.getWallTexture(isTop, isBottom, isLeft, isRight), x * 16, y * 16, sf::IntRect(0, 0, 16, 16));
                    }
                }
            }
            std::cout << "index: " << z << std::endl;
            std::cout << " | wallsTexture size: " << wallImage.getSize().x << " x " << wallImage.getSize().y << std::endl;
            std::cout << " | floorTexture size: " << floorImage.getSize().x << " x " << floorImage.getSize().y << std::endl;

            mapTexture.floorTexture.push_back(floorImage);
            mapTexture.wallTexture.push_back(wallImage);

            floorImage.create(map.getSizeX() * TILE_SIZE, map.getSizeY() * TILE_SIZE, sf::Color::Black);
            wallImage.create(map.getSizeX() * TILE_SIZE, map.getSizeY() * TILE_SIZE, sf::Color(0, 0, 0, 0));
        }
        return mapTexture;
    }

} // namespace MapTextureGenerator


#endif