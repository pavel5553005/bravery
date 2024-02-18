#include "../ObjOnLayout.hpp"
#include "../../Event/Event.hpp"
#include "../../Event/EventHandler.hpp"
#include "../../Map/Layout.hpp"

class DebugObj : public ObjOnLayout
{
private:
    ObjOnLayout* followObj;
public:
    DebugObj();
    DebugObj(Coordinates pos, Vector2d size, Layout* layout, ObjOnLayout* followObj);
    void generateEvent();
    void event(Event event);
};

DebugObj::DebugObj()
{
    
}

DebugObj::DebugObj(Coordinates pos, Vector2d size, Layout* layout, ObjOnLayout* followObj) : ObjOnLayout(pos, size, layout)
{
    eventHandler->addObject(this);
    this->followObj = followObj;
}

void DebugObj::event(Event event)
{
    if (event.type == Event::Type::ObjMove and event.objMove.obj == followObj)
    {
        setPos(event.objMove.end);
    }
}