#ifndef Layout_hpp_
#define Layout_hpp_
#include <list>
#include "Map.hpp"
#include "../ObjOnLayout/ObjOnLayout.hpp"
#include "../Event/EventHandler.hpp"

class Layout
{
private:
    std::list<ObjOnLayout*> objects;
    Map map;
    EventHandler* eventHandler;
public:
    Layout(EventHandler* eventHandler);
    void addObject(ObjOnLayout* obj);
    std::list<ObjOnLayout*> getObjects();
    void tick();
    Map* getMap();
    ~Layout();
};

Layout::Layout(EventHandler* eventHandler)
{
    this->eventHandler = eventHandler;
}

std::list<ObjOnLayout*> Layout::getObjects()
{
    return objects;
}

void Layout::addObject(ObjOnLayout* obj)
{
    objects.push_back(obj);
    obj->setEventHandler(eventHandler);
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