#include "../ObjOnLayout.hpp"
#include "../../Event/Event.hpp"
#include "../../Event/EventHandler.hpp"

class DebugObj : public ObjOnLayout
{
private:
    
public:
    DebugObj();
    void generateEvent();
    void eventFunc(Event::Type event);
};

DebugObj::DebugObj()
{}

void DebugObj::generateEvent()
{
    Event event(Event::Type::TestEvent);
    eventHandler->generateEvent(event);
}

void DebugObj::eventFunc(Event::Type event)
{
    /*
        Сгенерировать другую текстуру
    */
}