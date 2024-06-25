#ifndef Layout_hpp_
#define Layout_hpp_
#include <list>
#include "Map.hpp"
#include "../ObjOnLayout/ObjOnLayout.hpp"
#include "../Event/Event.hpp"
#include "../Event/EventHandler.hpp"

class Layout
{
private:
    std::list<ObjOnLayout*> objects;
    Map map;
public:
    Layout();

    std::list<ObjOnLayout*>& getObjects();
    Map& getMap();

    void generateEvent(Event event);
    void addObject(ObjOnLayout& obj);
    void deleteObject(ObjOnLayout& obj);
    void tick();
    virtual ~Layout();
};

Layout::Layout() { }

std::list<ObjOnLayout*>& Layout::getObjects() { return objects; }

Map& Layout::getMap() { return map; }

void Layout::addObject(ObjOnLayout& obj)
{
    debuger.consoleLog("add object");
    objects.push_back(&obj);
    debuger.consoleLog(std::to_string(objects.size()));
    // map.getCell(obj.getPos().x + obj.getSize().x / 2, obj.getPos().y + obj.getSize().y / 2, 0)->addObject(obj);
}

void Layout::deleteObject(ObjOnLayout& obj)
{
    debuger.consoleLog("delete object");
    objects.remove(&obj);
    debuger.consoleLog(std::to_string(objects.size()));
    // map.getCell(obj.getPos().x + obj.getSize().x / 2, obj.getPos().y + obj.getSize().y / 2, 0)->deleteObject(obj);
}

void Layout::tick()
{
    handler.generateEvent(Event(Event::Type::Tick));
}

Layout::~Layout()
{
    objects.clear();
}

#endif