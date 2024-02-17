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
    std::list<ObjOnLayout*>* getObjects();
    void tick();
    Map* getMap();
    ~Layout();
};

Layout::Layout(EventHandler* eventHandler)
{
    this->eventHandler = eventHandler;
}

std::list<ObjOnLayout*>* Layout::getObjects()
{
    return &objects;
}

void Layout::addObject(ObjOnLayout* obj)
{
    objects.push_back(obj);
    obj->setEventHandler(eventHandler);
    map.getCell(obj->getPos().x + obj->getSize().x / 2, obj->getPos().y + obj->getSize().y / 2, 0)->addObject(obj);
}

void Layout::tick()
{
    
}

Map *Layout::getMap()
{
    return &map;
}

Layout::~Layout()
{

}

#endif