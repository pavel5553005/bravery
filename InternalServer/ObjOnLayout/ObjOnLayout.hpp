#ifndef ObjOnLayout_hpp_
#define ObjOnLayout_hpp_

#include "../Coordinates.hpp"
#include "../Vector2d.hpp"

class Event;

class Layout;

class ObjOnLayout
{
private:
    Coordinates pos;
    Vector2d size;
protected:
    Layout* layout;
public:
    ObjOnLayout();
    ObjOnLayout(Coordinates pos, Vector2d size, Layout& layout);

    Coordinates getPos();
    Vector2d getSize();

    void setPos(Coordinates pos);

    virtual void event(Event event) = 0;
    void removeFromLayout();

    virtual ~ObjOnLayout();
};

#endif