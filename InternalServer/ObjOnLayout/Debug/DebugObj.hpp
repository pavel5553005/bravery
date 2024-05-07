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

    void setFollowObj(ObjOnLayout& followObj) { this->followObj = &followObj; }

    void sex(Event event) { setPos(Coordinates(followObj->getPos().x, followObj->getPos().y, followObj->getPos().z)); }

    ~DebugObj();
};

DebugObj::DebugObj() : ObjOnLayout() { }

DebugObj::DebugObj(Coordinates pos, Vector2d size, Layout& layout, ObjOnLayout& followObj) : ObjOnLayout(pos, size, layout)
{
    this->followObj = &followObj;
    handler.addListener(std::bind(&DebugObj::sex, this, std::placeholders::_1), Event::Type::TestEvent);
}

DebugObj::~DebugObj() { }