#include "ObjOnLayout.hpp"
#include "../Event/Event.hpp"
#include "../Event/EventHandler.hpp"
#include "../Map/Layout.hpp"
#include <iostream>

ObjOnLayout::ObjOnLayout()
{
    this->pos = Coordinates();
    this->size = Vector2d();
    layout = nullptr;
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
    if (pos.x > 100) pos.x = 100;
    if (pos.y > 100) pos.y = 100;
    if (pos.x < 0) pos.x = 0;
    if (pos.y < 0) pos.y = 0;

    layout->getMap()->getCell(this->pos.x + size.x / 2, this->pos.y + size.y / 2, 0)->deleteObject(this);
    this->pos = pos;
    layout->getMap()->getCell(this->pos.x + size.x / 2, this->pos.y + size.y / 2, 0)->addObject(this);
}

void ObjOnLayout::tick()
{

}

void ObjOnLayout::move(Coordinates delta)
{
    setPos(pos + delta);
}

void ObjOnLayout::removeFromLayout()
{
    if (layout != nullptr)
    {
        ObjOnLayout* temp = this;
        layout->getObjects()->remove(temp);
        layout->getMap()->getCell(this->pos.x + size.x / 2, this->pos.y + size.y / 2, 0)->deleteObject(temp);
    }
}

ObjOnLayout::~ObjOnLayout()
{
}
