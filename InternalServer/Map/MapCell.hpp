#ifndef MapCell_hpp_
#define MapCell_hpp_
#include "../ObjOnLayout/ObjOnLayout.hpp"
#include <list>

class MapCell
{
public:
    enum class Type { Grass, Stone, Ground, Water, None, Air};
private:
    Type type;
    std::list<ObjOnLayout*> objects;
public:
    MapCell();
    MapCell(Type type);

    Type getType();
    std::list<ObjOnLayout*>* getObjects();

    void addObject(ObjOnLayout& obj);
    void deleteObject(ObjOnLayout& obj);

    ~MapCell();
};

MapCell::MapCell()
{
    type = MapCell::Type::None;
}

MapCell::MapCell(MapCell::Type type)
{
    this->type = type;
}

MapCell::Type MapCell::getType()
{
    return type;
}

std::list<ObjOnLayout*>* MapCell::getObjects()
{
    return &objects;
}

void MapCell::addObject(ObjOnLayout& obj)
{
    objects.push_back(&obj);
}

void MapCell::deleteObject(ObjOnLayout& obj)
{
    objects.remove(&obj);
}

MapCell::~MapCell()
{
}

#endif