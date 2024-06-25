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
    MapCell(const FloorType floorType, const WallType wallType);

    const FloorType getFloorType();
    const WallType getWallType();
    // std::list<ObjOnLayout*>* getObjects();

    void setWallType(const WallType wallType);
    void setFloorType(const FloorType floorType);

    // void addObject(ObjOnLayout& obj);
    // void deleteObject(ObjOnLayout& obj);

    ~MapCell();
};

MapCell::MapCell() : floorType(FloorType::None), wallType(WallType::None) { }

MapCell::MapCell(FloorType floorType, WallType wallType = WallType::None) : floorType(floorType), wallType(wallType) { }

const MapCell::FloorType MapCell::getFloorType() { return floorType; }

const MapCell::WallType MapCell::getWallType() { return wallType; }

void MapCell::setWallType(WallType wallType) { this->wallType = wallType; }

void MapCell::setFloorType(FloorType floorType) { this->floorType = floorType; }

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