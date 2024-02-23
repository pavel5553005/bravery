#ifndef Map_hpp_
#define Map_hpp_
#include "MapCell.hpp"
#include "iostream"

class Map
{
private:
    int sizeX;
    int sizeY;
    int sizeZ;
    MapCell cells[1][100][100];
public:
    Map();
    Map(MapCell*** cells, int sizeX, int sizeY, int sizeZ);
    MapCell* getCell(int x, int y, int z);
    ~Map();
};

Map::Map()
{
    sizeX = 100;
    sizeY = 100;
    sizeZ = 1;
    for (int x = 0; x < 100; x++)
    {
        for (int y = 0; y < 100; y++)
        {
            if (x % 2 == 0 and y % 2 == 0 or y % 2 == 1 and x % 2 == 1)
            {
                cells[0][x][y] = MapCell(MapCell::FloorType::Grass);
            }
            else
            {
                cells[0][x][y] = MapCell(MapCell::FloorType::Stone);
            }
        }
        
    }

    for (int x = 10; x < 20; x++)
    {
        cells[0][x][10].setWallType(MapCell::WallType::Wall);
        cells[0][x][20].setWallType(MapCell::WallType::Wall);

    }
    for (int y = 10; y < 20; y++)
    {
        cells[0][10][y].setWallType(MapCell::WallType::Wall);
        cells[0][20][y].setWallType(MapCell::WallType::Wall);
    }
    for (int x = 0; x < 100; x++)
    {
        for (int y = 0; y < 100; y++)
        {
            if (cells[0][x][y].getWallType() == MapCell::WallType::Wall)
            {
                std::cout << '#';
            }
            else
            {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }
    
}

Map::Map(MapCell*** cells, int sizeX, int sizeY, int sizeZ)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->sizeZ = sizeZ;
}

MapCell* Map::getCell(int x, int y, int z)
{
    return &cells[z][x][y];
}

Map::~Map()
{

}


#endif