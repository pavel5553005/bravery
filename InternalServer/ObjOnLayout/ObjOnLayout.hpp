#ifndef ObjOnLayout_hpp_
#define ObjOnLayout_hpp_

#include "../Coordinates.hpp"
#include "../Vector2d.hpp"

class Event;

class EventHandler;

class ObjOnLayout
{
private:
    Coordinates pos;
    Vector2d size;
protected:
    EventHandler* eventHandler;
public:
    ObjOnLayout();
    ObjOnLayout(Coordinates pos, Vector2d size);
    Coordinates getPos();
    Vector2d getSize();
    void setEventHandler(EventHandler* eventHandler);
    void setPos(Coordinates pos);
    void tick();
    ~ObjOnLayout();
};

#endif