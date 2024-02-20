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

    std::list<ObjOnLayout*>* getObjects();
    Map* getMap();

    void addObject(ObjOnLayout* obj);
    void deleteObject(ObjOnLayout* obj);
    void tick();
    virtual ~Layout();
};

Layout::Layout(EventHandler* eventHandler)
{
    this->eventHandler = eventHandler;
}

std::list<ObjOnLayout*>* Layout::getObjects() { return &objects; }

Map *Layout::getMap() { return &map; }

void Layout::addObject(ObjOnLayout* obj)
{
    objects.push_back(obj);
    obj->setEventHandler(eventHandler);
    map.getCell(obj->getPos().x + obj->getSize().x / 2, obj->getPos().y + obj->getSize().y / 2, 0)->addObject(obj);
}

void Layout::deleteObject(ObjOnLayout* obj)
{
    objects.remove(obj);
    map.getCell(obj->getPos().x + obj->getSize().x / 2, obj->getPos().y + obj->getSize().y / 2, 0)->deleteObject(obj);
}

void Layout::tick()
{
    for (auto i : objects)
    {
        i->tick();
    }
}

Layout::~Layout()
{

}

#endif