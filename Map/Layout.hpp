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
    void tick();
    Map* getMap();
    ~Layout();
};

Layout::Layout()
{}



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
    for (ObjOnLayout* i : objects)
    {
        i->tick();
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