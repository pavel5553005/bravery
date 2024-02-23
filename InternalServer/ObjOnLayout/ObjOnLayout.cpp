#include "ObjOnLayout.hpp"
#include "../Event/Event.hpp"
#include "../Map/Layout.hpp"
#include <iostream>

ObjOnLayout::ObjOnLayout()
{
    this->pos = Coordinates();
    this->size = Vector2d();
    layout = nullptr;
}

ObjOnLayout::ObjOnLayout(Coordinates pos, Vector2d size, Layout& layout)
{
    this->pos = pos;
    this->size = size;
    this->layout = &layout;
    layout.addObject(*this);
    Event event(Event::Type::ObjSpawn);
    event.objSpawn.obj = this;
    event.objSpawn.pos = pos;
    layout.generateEvent(event);
}

Coordinates ObjOnLayout::getPos()
{
    return pos;
}

Vector2d ObjOnLayout::getSize()
{
    return size;
}

void ObjOnLayout::setPos(Coordinates pos)
{
    if (pos.x + size.x > 100) pos.x = 100 - size.x;
    if (pos.y + size.y > 100) pos.y = 100 - size.y;
    if (pos.x < 0) pos.x = 0;
    if (pos.y < 0) pos.y = 0;

    layout->getMap()->getCell(this->pos.x + size.x / 2, this->pos.y + size.y / 2, 0)->deleteObject(*this);

    this->pos = pos;
    
    layout->getMap()->getCell(this->pos.x + size.x / 2, this->pos.y + size.y / 2, 0)->addObject(*this);
}

// void ObjOnLayout::event(Event event) { }

void ObjOnLayout::removeFromLayout()
{
    if (layout != nullptr)
    {
        layout->deleteObject(*this);
    }
}

void ObjOnLayout::event(Event event) { }

ObjOnLayout::~ObjOnLayout()
{
    removeFromLayout();
}