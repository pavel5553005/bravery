#ifndef ObjOnLayout_hpp_
#define ObjOnLayout_hpp_

#include "../Position/Coordinates.hpp"
#include "../Position/Vector2d.hpp"
#include "../AnimatedTexture.hpp"
#include "../../Resources/ResourceManager.hpp"

class Event;

class Layout;

class ObjOnLayout
{
private:
    Coordinates pos;
    Vector2d size;
    Vector2d center;
    bool isCollide(double x, double y, double z);
    Vector2d maxDPoint(Coordinates pos, Coordinates newPos, bool isVertex);
    static Vector2d maxVextorOfModule(Vector2d a, Vector2d b)
    {
        Vector2d result;
        result.x = abs(a.x) < abs(b.x) ? a.x : b.x;
        result.y = abs(a.y) < abs(b.y) ? a.y : b.y;
        return result;
    }
protected:
    AnimatedTexture texture;
    Layout* layout;
public:
    ObjOnLayout();
    ObjOnLayout(Coordinates pos, Vector2d size, Layout& layout);

    Coordinates getPos();
    Vector2d getSize();
    AnimatedTexture getTexture() { return texture; }

    void updateTexture(Event event);

    void setPos(Coordinates pos);
    
    void removeFromLayout();

    virtual ~ObjOnLayout();
};

#endif