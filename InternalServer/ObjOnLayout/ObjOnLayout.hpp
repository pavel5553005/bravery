#ifndef ObjOnLayout_hpp_
#define ObjOnLayout_hpp_

#include "../Position/Coordinates.hpp"
#include "../Position/Vector2d.hpp"
#include "../AnimatedTexture.hpp"
#include "../../Resources/ResourceManager.hpp"
#include "../../Exception/EmptyLayout.hpp"

class Event;

class Layout;

class ObjOnLayout
{
private:
    Coordinates pos;
    Vector2d size;
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
    ObjOnLayout(const Coordinates pos, const Vector2d size);

    Coordinates getPos() const { return pos; }
    Vector2d getSize() const { return size; }
    AnimatedTexture getTexture() const { return texture; }
    Layout& getLayout() const;

    void updateTexture(Event event);

    void setPos(const Coordinates pos);
    void setLayout(Layout& layout);
    
    void removeFromLayout();

    virtual ~ObjOnLayout();
};

#endif