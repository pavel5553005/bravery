#include "ObjOnLayout.hpp"
#include "../Event/Event.hpp"
#include "../Event/EventHandler.hpp"
#include "../Map/Layout.hpp"
#include <iostream>

ObjOnLayout::ObjOnLayout()
{
    this->pos = Coordinates();
    this->size = Vector2d();
}

ObjOnLayout::ObjOnLayout(Coordinates pos, Vector2d size, Layout* layout)
{
    this->pos = pos;
    this->size = size;
    std::cout << "ObjOnLayout:" << size.x << " " << size.y << std::endl;
    this->layout = layout;
    layout->addObject(this);
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
