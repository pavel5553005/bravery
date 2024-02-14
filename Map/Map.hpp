#ifndef Map_hpp_
#define Map_hpp_
#include "FloorCell.hpp"

class Map
{
private:
    int sizeX;
    int sizeY;
    int sizeZ;
    FloorCell cells[1][100][100];
public:
    Map();
    Map(FloorCell*** cells, int sizeX, int sizeY, int sizeZ);
    FloorCell getCell(int x, int y, int z);
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
            if (x % 2 == 0 and y % 2 == 0 or x % 2 == 1 and y % 2 == 1)
            {
                cells[0][x][y] = FloorCell(FloorCellType::Grass);
            }
            else
            {
                cells[0][x][y] = FloorCell(FloorCellType::Stone);
            }
        }
        
    }
    
}

Map::Map(FloorCell*** cells, int sizeX, int sizeY, int sizeZ)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->sizeZ = sizeZ;
}

FloorCell Map::getCell(int x, int y, int z)
{
    return cells[z][x][y];
}

Map::~Map()
{

}


#endif