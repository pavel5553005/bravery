#include "../ObjOnLayout.hpp"
#include "../../Event/Event.hpp"
#include "../../Map/Layout.hpp"

class DebugObj : public ObjOnLayout
{
private:
    ObjOnLayout* followObj;
public:
    DebugObj();
    DebugObj(Coordinates pos, Vector2d size, Layout& layout, ObjOnLayout& followObj);

    void generateEvent();
    void event(Event event);
    ~DebugObj();
};

DebugObj::DebugObj() : ObjOnLayout() { }

DebugObj::DebugObj(Coordinates pos, Vector2d size, Layout& layout, ObjOnLayout& followObj) : ObjOnLayout(pos, size, layout)
{
    this->followObj = &followObj;
}

void DebugObj::generateEvent() { }

void DebugObj::event(Event event)
{
    if (event.type == Event::Type::Tick)
    {
        DebugObj::setPos(followObj->getPos());
    }
}

DebugObj::~DebugObj() { }