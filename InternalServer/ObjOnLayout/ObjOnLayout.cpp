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

    if (newPos.x + size.x > layout->getMap()->getSizeX()) newPos.x = layout->getMap()->getSizeX() - size.x;
    if (newPos.y + size.y > layout->getMap()->getSizeY()) newPos.y = layout->getMap()->getSizeY() - size.y;
    if (newPos.z >= layout->getMap()->getSizeZ()) newPos.z = layout->getMap()->getSizeZ() - 1;
    if (newPos.x < 0) newPos.x = 0;
    if (newPos.y < 0) newPos.y = 0;
    if (newPos.z < 0) newPos.z = 0;
    
    Vector2d maxD = newPos - pos;
    maxD = maxVextorOfModule(maxD, maxDPoint(pos, newPos, true));
    maxD = maxVextorOfModule(maxD, maxDPoint(Coordinates(pos.x + size.x, pos.y, pos.z), Coordinates(newPos.x + size.x, newPos.y, newPos.z), true));
    maxD = maxVextorOfModule(maxD, maxDPoint(Coordinates(pos.x, pos.y + size.y, pos.z), Coordinates(newPos.x, newPos.y + size.y, newPos.z), true));
    maxD = maxVextorOfModule(maxD, maxDPoint(pos + size, newPos + size, true));

    // for (int x = pos.x; x < pos.x + size.x; x++)
    // {
    //     if (newPos.y - pos.y > 0 and isCollide(x, newPos.y + size.y, pos.z))
    //     {
    //         newPos.y = int(newPos.y + size.y) - size.y;
    //         break;
    //     }
    //     else if (newPos.y - pos.y < 0 and isCollide(x, newPos.y, pos.z))
    //     {
    //         newPos.y = int(newPos.y) + 1;
    //         break;
    //     }
    // }
    // for (int y = pos.y; y < pos.y + size.y; y++)
    // {
    //     if (newPos.x - pos.x > 0 and isCollide(newPos.x + size.x, y, pos.z))
    //     {
    //         newPos.x = int(newPos.x + size.x) - smaxDize.x;
    //         break;
    //     }
    //     else if (newPos.x - pos.x < 0 and isCollide(newPos.x, y, pos.z))
    //     {
    //         newPos.x = int(newPos.x) + 1;
    //         break;
    //     }
    // }

    newPos = pos + maxD;

    if (newPos == pos) return;

    // layout->getMap()->getCell(this->pos.x + size.x / 2, this->pos.y + size.y / 2, 0)->deleteObject(*this);

    this->pos = newPos;
    
    // layout->getMap()->getCell(this->pos.x + size.x / 2, this->pos.y + size.y / 2, 0)->addObject(*this);
}

// void ObjOnLayout::event(Event event) { }

bool ObjOnLayout::isCollide(double x, double y, double z)
{
    if (layout->getMap()->getCell(x, y, z) == nullptr)
    {
        return false;
    }
    return layout->getMap()->getCell(x, y, z)->getWallType() != MapCell::WallType::None;
}

Vector2d ObjOnLayout::maxDPoint(Coordinates pos, Coordinates newPos, bool isVertex)
{
    Vector2d maxD = newPos - pos;
    if (isCollide(pos.x, newPos.y, newPos.z) and !(pos.x == int(pos.x) and isVertex))
    {
        if (newPos.y - pos.y < 0 and int(newPos.y) + 1 - pos.y > maxD.y)
        {
            maxD.y = int(newPos.y) + 1 - pos.y;
        }
        if (newPos.y - pos.y > 0 and int(newPos.y) - pos.y < maxD.y)
        {
            maxD.y = int(newPos.y) - pos.y;
        }
    }
    if (isCollide(newPos.x, pos.y, newPos.z) and !(pos.y == int(pos.y) and isVertex))
    {
        if (newPos.x - pos.x < 0 and int(newPos.x) + 1 - pos.x > maxD.x)
        {
            maxD.x = int(newPos.x) + 1 - pos.x;
        }
        if (newPos.x - pos.x > 0 and int(newPos.x) - pos.x < maxD.x)
        {
            maxD.x = int(newPos.x) - pos.x;
        }
    }
    return maxD;
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