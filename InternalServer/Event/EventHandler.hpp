#ifndef EventHandler_hpp_
#define EventHandler_hpp_
#include "Event.hpp"
#include <list>
#include "../ObjOnLayout/ObjOnLayout.hpp"
#include <iostream>

class EventHandler
{
private:
    std::list<ObjOnLayout*> objects;
public:
    EventHandler();
    void addObject(ObjOnLayout* obj);
    void deleteObject(ObjOnLayout* obj);
    void generateEvent(Event event);
};

EventHandler::EventHandler()
{

}

void EventHandler::addObject(ObjOnLayout* obj)
{
    objects.push_back(obj);
}

void EventHandler::deleteObject(ObjOnLayout* obj)
{
    objects.remove(obj);
}

void EventHandler::generateEvent(Event event)
{
    for (auto i : objects)
    {
        i->event(event);
    }
}

#endif