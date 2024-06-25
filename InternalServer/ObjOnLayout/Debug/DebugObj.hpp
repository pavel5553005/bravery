#include "../ObjOnLayout.hpp"
#include "../../Event/Event.hpp"
#include "../../Map/Layout.hpp"

class DebugObj : public ObjOnLayout
{
private:
    const ObjOnLayout* followObj;
public:
    DebugObj();
    DebugObj(const Coordinates pos, const Vector2d size, ObjOnLayout& followObj);

    void setFollowObj(ObjOnLayout& followObj) { this->followObj = &followObj; }

    void sex(Event event) { setPos(Coordinates(followObj->getPos().x, followObj->getPos().y, followObj->getPos().z)); }

    ~DebugObj();
};

DebugObj::DebugObj() : ObjOnLayout() { }

DebugObj::DebugObj(const Coordinates pos, const Vector2d size, ObjOnLayout& followObj) :
ObjOnLayout(pos, size),
followObj(&followObj)
{
    handler.addListener(std::bind(&DebugObj::sex, this, std::placeholders::_1), Event::Type::TestEvent);
}

DebugObj::~DebugObj() { }