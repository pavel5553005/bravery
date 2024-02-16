#ifndef EventHandler_hpp_
#define EventHandler_hpp_
#include "Event.hpp"
#include <list>
#include "../ObjOnLayout/ObjOnLayout.hpp"

class EventHandler
{
private:
    struct ObjAndPpinter
    {
        ObjOnLayout* obj;
        void (*func) (Event);
    };
    
    std::list<ObjAndPpinter> objects;
public:
    EventHandler();
    void addObject(ObjOnLayout* obj, void (*func) (Event));
    void deleteObject(ObjOnLayout* obj);
    void generateEvent(Event event);
};

EventHandler::EventHandler()
{

}

void EventHandler::addObject(ObjOnLayout* obj, void (*func) (Event))
{
    ObjAndPpinter temp;
    temp.obj = obj;
    temp.func = func;
    objects.push_back(temp);
}

void EventHandler::deleteObject(ObjOnLayout* obj)
{
    for (auto i = objects.begin(); i != objects.end(); i++)
    {
        if (i->obj == obj)
        {
            objects.erase(i);
            break;
        }
    }
}

void EventHandler::generateEvent(Event event)
{
    for (ObjAndPpinter i : objects)
    {
        i.func(event);
    }
}

#endif