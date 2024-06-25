#ifndef Map_hpp_
#define Map_hpp_
#include "MapCell.hpp"
#include "iostream"
#include <vector>

class Map
{
private:
    const int sizeX;
    const int sizeY;
    const int sizeZ;
    std::vector<std::vector<std::vector<MapCell>>> cells;
public:
    Map();

    MapCell& getCell(int x, int y, int z);
    MapCell& getCell(Coordinates pos);
    int getSizeX() {return sizeX;}
    int getSizeY() {return sizeY;}
    int getSizeZ() {return sizeZ;}

    ~Map();
};

Map::Map() : sizeX(10), sizeY(10), sizeZ(10) {
    std::cout << sizeX << " " << sizeY << " " << sizeZ << std::endl;

    cells = std::vector<std::vector<std::vector<MapCell>>>(sizeZ, std::vector<std::vector<MapCell>>(sizeX, std::vector<MapCell>(sizeY)));
    
    for (int z = 0; z < sizeZ; z++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            for (int y = 0; y < sizeY; y++)
            {
                cells[z][x][y] = MapCell(MapCell::FloorType::Grass);
                if (z == 0 and ((y == 4 and x >= 3 and x <= 8) or (y == 8 and x >= 3 and x <= 8) or (x == 3 and y >= 4 and y <= 8) or (x == 8 and y >= 4 and y <= 8)))
                {
                    cells[z][x][y].setWallType(MapCell::WallType::Wall);
                }
                if (3 <= x and x <= 8 and 4 <= y and y <= 8)
                {
                    cells[z][x][y].setFloorType(MapCell::FloorType::Stone);
                }
            }
        }
    }
    cells[0][6][4].setWallType(MapCell::WallType::None);
    cells[0][7][3].setWallType(MapCell::WallType::Wall);
}

MapCell& Map::getCell(int x, int y, int z)
{
    if (x < 0 or x >= sizeX or y < 0 or y >= sizeY or z < 0 or z >= sizeZ)
    {
        throw std::out_of_range("Coordinates out of range");
    }
    
    return cells[z][x][y];
}

MapCell& Map::getCell(Coordinates pos)
{
    return getCell(pos.x, pos.y, pos.z);
}

Map::~Map()
{
    std::exit(0);
}


#endif