#ifndef Layout_hpp_
#define Layout_hpp_
#include <list>
#include "Map.hpp"
#include "../ObjOnLayout/ObjOnLayout.hpp"

class Layout
{
private:
    std::list<ObjOnLayout*> objects;
    Map map;
public:
    Layout();
    void addObject(ObjOnLayout* obj);
    bool isCollide(ObjOnLayout* obj);
    std::list<ObjOnLayout*> getObjects();
    void tick();
    Map* getMap();
    ~Layout();
};

Layout::Layout()
{}

std::list<ObjOnLayout*> Layout::getObjects()
{
    return objects;
}

void Layout::addObject(ObjOnLayout* obj)
{
    objects.push_back(obj);
}

bool Layout::isCollide(ObjOnLayout* obj)
{
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        if (obj->getPos().x < (*it)->getPos().x + (*it)->getSize().getX() &&
            obj->getPos().x + obj->getSize().getX() > (*it)->getPos().x &&
            obj->getPos().y < (*it)->getPos().y + (*it)->getSize().getY() &&
            obj->getPos().y + obj->getSize().getY() > (*it)->getPos().y)
        {
            return true;
        }
    }
    return false;
}

void Layout::tick()
{
    for (int z = 0; z < 1; z++)
    {
        for (int x = 0; x < 100; x++)
        {
            for (int y = 0; y < 100; y++)
            {
                map.getCell(x, y, z)->setObj(nullptr);
            }
        }
    }
    for (ObjOnLayout* i : objects)
    {
        i->tick();
        map.getCell(i->getPos().x, i->getPos().y, 0)->setObj(i);
    }
}

Map *Layout::getMap()
{
    return &map;
}

Layout::~Layout()
{

}

#endif