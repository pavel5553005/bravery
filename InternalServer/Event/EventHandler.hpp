#ifndef EVENTHANDLER_HPP_
#define EVENTHANDLER_HPP_

#include "Event.hpp"
#include <list>
#include <functional>

class EventHandler
{
private:
    struct ObjListener
    {
        std::function<void(Event)> func;
        Event::Type type;
    };
    std::list<ObjListener> listeners;
    
public:
    EventHandler();

    void generateEvent(Event event);

    void addListener(std::function<void(Event)> func, Event::Type type);

    ~EventHandler();
};

EventHandler::EventHandler() { }

void EventHandler::generateEvent(Event event)
{
    for (auto i : listeners)
    {
        if (i.type == event.type)
        {
            i.func(event);
        }
    }
}

void EventHandler::addListener(std::function<void(Event)> func, Event::Type type)
{
    ObjListener listener;
    listener.func = func;
    listener.type = type;
    listeners.push_back(listener);
}

EventHandler::~EventHandler()
{
    listeners.clear();
}

EventHandler handler;

#endif