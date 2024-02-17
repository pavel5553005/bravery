#ifndef LayoutCell_hpp_
#define LayoutCell_hpp_
#include "../ObjOnLayout/ObjOnLayout.hpp"
#include <list>

enum LayoutCellType { Grass, Stone, Ground, Water, None, Air};

class LayoutCell
{
private:
    LayoutCellType type;
    std::list<ObjOnLayout*> objects;
public:
    LayoutCell();
    LayoutCell(LayoutCellType type);
    LayoutCellType getType();
    void addObject(ObjOnLayout* obj);
    void deleteObject(ObjOnLayout* obj);
    std::list<ObjOnLayout*>* getObjects();
    ~LayoutCell();
};

LayoutCell::LayoutCell()
{
    type = None;
}

LayoutCell::LayoutCell(LayoutCellType type)
{
    this->type = type;
}

void LayoutCell::addObject(ObjOnLayout* obj)
{
    objects.push_back(obj);
}

void LayoutCell::deleteObject(ObjOnLayout* obj)
{
    objects.remove(obj);
}

std::list<ObjOnLayout*>* LayoutCell::getObjects()
{
    return &objects;
}

LayoutCellType LayoutCell::getType()
{
    return type;
}

LayoutCell::~LayoutCell()
{
}


#endif