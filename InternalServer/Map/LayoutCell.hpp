#ifndef LayoutCell_hpp_
#define LayoutCell_hpp_
#include "../ObjOnLayout/ObjOnLayout.hpp"

enum LayoutCellType { Grass, Stone, Ground, Water, None, Air};

class LayoutCell
{
private:
    LayoutCellType type;
    ObjOnLayout* obj;
public:
    LayoutCell();
    LayoutCell(LayoutCellType type);
    LayoutCellType getType();
    void setObj(ObjOnLayout* obj);
    ObjOnLayout* getObj();
    ~LayoutCell();
};

LayoutCell::LayoutCell()
{
    type = None;
    obj = nullptr;
}

LayoutCell::LayoutCell(LayoutCellType type)
{
    this->type = type;
}

void LayoutCell::setObj(ObjOnLayout *obj)
{
    this->obj = obj;
}

ObjOnLayout* LayoutCell::getObj()
{
    return obj;
}

LayoutCellType LayoutCell::getType()
{
    return type;
}

LayoutCell::~LayoutCell()
{
}


#endif