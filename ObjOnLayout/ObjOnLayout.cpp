#include "ObjOnLayout.hpp"
#include "../Map/Layout.hpp"

ObjOnLayout::ObjOnLayout()
{
    this->pos = Coordinates();
    pos.x = 0;
    pos.y = 0;
    pos.z = 0;
    this->size = Vector2d();
}

ObjOnLayout::ObjOnLayout(Coordinates pos, Vector2d size, Layout* layout)
{
    this->pos = pos;
    this->size = size;
    this->layout = layout;
    this->layout->addObject(this);
}

ObjOnLayout::~ObjOnLayout()
{
}

Coordinates ObjOnLayout::getPos()
{
    return pos;
}