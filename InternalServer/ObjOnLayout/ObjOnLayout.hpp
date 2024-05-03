#ifndef ObjOnLayout_hpp_
#define ObjOnLayout_hpp_

#include "../Position/Coordinates.hpp"
#include "../Position/Vector2d.hpp"

class Event;

class Layout;

class ObjOnLayout
{
private:
    Coordinates pos;
    Vector2d size;
    Vector2d center;
    bool isCollide(int x, int y, int z);
protected:
    Layout* layout;
public:
    ObjOnLayout();
    ObjOnLayout(Coordinates pos, Vector2d size, Layout& layout);

    Coordinates getPos();
    Vector2d getSize();

    void setPos(Coordinates pos);
    
    void removeFromLayout();

    virtual ~ObjOnLayout();
};

#endif