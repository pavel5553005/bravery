#ifndef Map_hpp_
#define Map_hpp_
#include "MapCell.hpp"
#include "iostream"

class Map
{
private:
    const int sizeX;
    const int sizeY;
    const int sizeZ;
    MapCell*** cells;
public:
    Map();
    Map(MapCell*** cells, int sizeX, int sizeY, int sizeZ);
    MapCell* getCell(int x, int y, int z);
    int getSizeX() {return sizeX;}
    int getSizeY() {return sizeY;}
    int getSizeZ() {return sizeZ;}
    ~Map();
};

Map::Map() : sizeX(10), sizeY(10), sizeZ(1) {
    for (int x = 0; x < sizeX; x++)
    {
        for (int y = 0; y < sizeY; y++)
        {
            if (x % 2 == 0 and y % 2 == 0)
            {
                cells[0][x][y] = MapCell(MapCell::FloorType::Grass);
            }
            else
            {
                cells[0][x][y] = MapCell(MapCell::FloorType::Ground);
            }
        }
    }
    
}

Map::Map(MapCell*** cells, int sizeX, int sizeY, int sizeZ) : cells(cells), sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ) { }

MapCell* Map::getCell(int x, int y, int z)
{
    return &cells[z][x][y];
}

Map::~Map()
{
    for (int x = 0; x < sizeX; x++)
    {
        for (int y = 0; y < sizeY; y++)
        {
            cells[0][x][y].~MapCell();
        }
    }
}


#endif