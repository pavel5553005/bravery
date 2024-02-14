#ifndef ObjOnLayout_hpp_
#define ObjOnLayout_hpp_

#include "Coordinates.hpp"
#include "Vector2d.hpp"

class Layout;

class ObjOnLayout
{
private:
    Coordinates pos;
    Vector2d size;
    Layout* layout;
public:
    ObjOnLayout();
    ObjOnLayout(Coordinates pos, Vector2d size, Layout* layout);
    ~ObjOnLayout();
    Coordinates getPos();
    Vector2d getSize();
    void setPos(Coordinates pos);
    void tick();
};

#endif