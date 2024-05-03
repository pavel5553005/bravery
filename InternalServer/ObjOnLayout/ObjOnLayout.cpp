#include "ObjOnLayout.hpp"
#include "../Event/Event.hpp"
#include "../Map/Layout.hpp"
#include <iostream>

ObjOnLayout::ObjOnLayout()
{
    this->pos = Coordinates();
    this->size = Vector2d();
    this->center = Vector2d();
    this->layout = nullptr;
}

ObjOnLayout::ObjOnLayout(Coordinates pos, Vector2d size, Layout& layout)
{
    this->size = size;
    this->layout = &layout;
    this->setPos(pos);
    layout.addObject(*this);
    Event event(Event::Type::ObjSpawn);
    event.objSpawn.obj = this;
    event.objSpawn.pos = pos;
    handler.generateEvent(event);
}

Coordinates ObjOnLayout::getPos()
{
    return pos;
}

Vector2d ObjOnLayout::getSize()
{
    return size;
}

void ObjOnLayout::setPos(Coordinates newPos)
{
    if (newPos == pos) return;

    if (newPos.x + size.x > 100) newPos.x = 100 - size.x;
    if (newPos.y + size.y > 100) newPos.y = 100 - size.y;
    if (newPos.x < 0) newPos.x = 0;
    if (newPos.y < 0) newPos.y = 0;

    for (int x = pos.x; x < pos.x + size.x; x++)
    {
        if (newPos.y - pos.y > 0 and isCollide(x, newPos.y + size.y, pos.z))
        {
            newPos.y = int(newPos.y + size.y) - size.y;
            break;
        }
        else if (newPos.y - pos.y < 0 and isCollide(x, newPos.y, pos.z))
        {
            newPos.y = int(newPos.y) + 1;
            break;
        }
    }
    for (int y = pos.y; y < pos.y + size.y; y++)
    {
        if (newPos.x - pos.x > 0 and isCollide(newPos.x + size.x, y, pos.z))
        {
            newPos.x = int(newPos.x + size.x) - size.x;
            break;
        }
        else if (newPos.x - pos.x < 0 and isCollide(newPos.x, y, pos.z))
        {
            newPos.x = int(newPos.x) + 1;
            break;
        }
    }

    if (newPos == pos) return;

    // layout->getMap()->getCell(this->pos.x + size.x / 2, this->pos.y + size.y / 2, 0)->deleteObject(*this);

    this->pos = newPos;
    
    // layout->getMap()->getCell(this->pos.x + size.x / 2, this->pos.y + size.y / 2, 0)->addObject(*this);
}

// void ObjOnLayout::event(Event event) { }

bool ObjOnLayout::isCollide(int x, int y, int z)
{
    return layout->getMap()->getCell(x, y, z)->getWallType() != MapCell::WallType::None;
}

void ObjOnLayout::removeFromLayout()
{
    if (layout != nullptr)
    {
        layout->deleteObject(*this);
        layout = nullptr;
    }
}

ObjOnLayout::~ObjOnLayout()
{
    removeFromLayout();
}