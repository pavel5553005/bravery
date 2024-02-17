#ifndef ObjOnLayout_hpp_
#define ObjOnLayout_hpp_

#include "../Coordinates.hpp"
#include "../Vector2d.hpp"

class Event;

class EventHandler;

class Layout;

class ObjOnLayout
{
private:
    Coordinates pos;
    Vector2d size;
protected:
    EventHandler* eventHandler;
    Layout* layout;
public:
    ObjOnLayout();
    ObjOnLayout(Coordinates pos, Vector2d size, Layout* layout);
    Coordinates getPos();
    Vector2d getSize();
    void setEventHandler(EventHandler* eventHandler);
    void setPos(Coordinates pos);
    void move(Coordinates delta);
    void tick();
    void removeFromLayout();
    ~ObjOnLayout();
};

#endif