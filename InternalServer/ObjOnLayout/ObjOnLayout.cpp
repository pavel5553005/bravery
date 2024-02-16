#include "ObjOnLayout.hpp"
#include "../Event/Event.hpp"
#include "../Event/EventHandler.hpp"

ObjOnLayout::ObjOnLayout()
{
    this->pos = Coordinates();
    pos.x = 0;
    pos.y = 0;
    pos.z = 0;
    this->size = Vector2d();
}

ObjOnLayout::ObjOnLayout(Coordinates pos, Vector2d size)
{
    this->pos = pos;
    this->size = size;
}

Coordinates ObjOnLayout::getPos()
{
    return pos;
}

Vector2d ObjOnLayout::getSize()
{
    return size;
}

void ObjOnLayout::setEventHandler(EventHandler* eventHandler)
{
    this->eventHandler = eventHandler;
}

void ObjOnLayout::setPos(Coordinates pos)
{
    this->pos = pos;
}

void ObjOnLayout::tick()
{

}

ObjOnLayout::~ObjOnLayout()
{
    
}
