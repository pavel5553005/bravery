#ifndef MapCell_hpp_
#define MapCell_hpp_
#include "../ObjOnLayout/ObjOnLayout.hpp"
#include <list>

class MapCell
{
public:
    enum class FloorType { Grass, Stone, Ground, Water, None};
    enum class WallType { Wall, None };
private:
    FloorType floorType;
    WallType wallType;
    // std::list<ObjOnLayout*> objects;
public:
    MapCell();
    MapCell(FloorType floorType, WallType wallType);

    FloorType getFloorType();
    WallType getWallType();
    // std::list<ObjOnLayout*>* getObjects();

    void setWallType(WallType wallType);

    // void addObject(ObjOnLayout& obj);
    // void deleteObject(ObjOnLayout& obj);

    ~MapCell();
};

MapCell::MapCell()
{
    floorType = MapCell::FloorType::None;
    wallType = MapCell::WallType::None;
}

MapCell::MapCell(FloorType floorType, WallType wallType = WallType::None)
{
    this->floorType = floorType;
    this->wallType = wallType;
}

MapCell::FloorType MapCell::getFloorType() { return floorType; }

MapCell::WallType MapCell::getWallType() { return wallType; }

void MapCell::setWallType(WallType wallType) { this->wallType = wallType; }

// std::list<ObjOnLayout*>* MapCell::getObjects()
// {
//     return &objects;
// }

// void MapCell::addObject(ObjOnLayout& obj)
// {
//     objects.push_back(&obj);
// }

// void MapCell::deleteObject(ObjOnLayout& obj)
// {
//     objects.remove(&obj);
// }

MapCell::~MapCell()
{
    // objects.clear();
}

#endif