#ifndef Layout_hpp_
#define Layout_hpp_
#include <list>
#include "Map.hpp"
#include "../ObjOnLayout/ObjOnLayout.hpp"
#include "../Event/Event.hpp"

class Layout
{
private:
    std::list<ObjOnLayout*> objects;
    Map map;
public:
    Layout();

    std::list<ObjOnLayout*>* getObjects();
    Map* getMap();

    void generateEvent(Event event);
    void addObject(ObjOnLayout& obj);
    void deleteObject(ObjOnLayout& obj);
    void tick();
    virtual ~Layout();
};

Layout::Layout() { }

std::list<ObjOnLayout*>* Layout::getObjects() { return &objects; }

Map *Layout::getMap() { return &map; }

void Layout::generateEvent(Event event)
{
    for (auto i : objects)
    {
        i->event(event);
    }
}

void Layout::addObject(ObjOnLayout& obj)
{
    objects.push_back(&obj);
    map.getCell(obj.getPos().x + obj.getSize().x / 2, obj.getPos().y + obj.getSize().y / 2, 0)->addObject(obj);
}

void Layout::deleteObject(ObjOnLayout& obj)
{
    objects.remove(&obj);
    map.getCell(obj.getPos().x + obj.getSize().x / 2, obj.getPos().y + obj.getSize().y / 2, 0)->deleteObject(obj);
}

void Layout::tick()
{
    Layout::generateEvent(Event(Event::Type::Tick));
}

Layout::~Layout()
{

}

#endif