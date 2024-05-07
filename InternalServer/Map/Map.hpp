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
    MapCell* getCell(Coordinates pos);
    int getSizeX() {return sizeX;}
    int getSizeY() {return sizeY;}
    int getSizeZ() {return sizeZ;}

    ~Map();
};

Map::Map() : sizeX(100), sizeY(100), sizeZ(100) {
    std::cout << sizeX << " " << sizeY << " " << sizeZ << std::endl;
    cells = new MapCell**[sizeZ];

    for (int z = 0; z < sizeZ; z++)
    {
        cells[z] = new MapCell*[sizeX];
        for (int x = 0; x < sizeX; x++)
        {
            cells[z][x] = new MapCell[sizeY];
        }
    }
    
    for (int z = 0; z < sizeZ; z++)
    {
        for (int x = 0; x < sizeX; x++)
        {
            for (int y = 0; y < sizeY; y++)
            {
                if ((x-50)*(x-50) + (y-50)*(y-50) + (z-50)*(z-50) <= 50*50)
                {
                    cells[z][x][y] = MapCell(MapCell::FloorType::Grass, MapCell::WallType::Wall);
                }
                else
                {
                    cells[z][x][y] = MapCell(MapCell::FloorType::Stone);
                }
                if ((x-50)*(x-50) + (y-50)*(y-50) + (z-50)*(z-50) == 50*50)
                {
                    cells[z][x][y].setWallType(MapCell::WallType::Wall);
                }
            }
        }
    }
}

Map::Map(MapCell*** cells, int sizeX, int sizeY, int sizeZ) : cells(cells), sizeX(sizeX), sizeY(sizeY), sizeZ(sizeZ) { }

MapCell* Map::getCell(int x, int y, int z)
{
    return &cells[z][x][y];
}

MapCell* Map::getCell(Coordinates pos)
{
    return getCell(pos.x, pos.y, pos.z);
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