#ifndef FloorCell_hpp_
#define FloorCell_hpp_

enum FloorCellType { Grass, Stone, Ground, Water, None, Air};

class FloorCell
{
private:
    FloorCellType type;
public:
    FloorCell();
    FloorCell(FloorCellType type);
    FloorCellType getType();
    ~FloorCell();
};

FloorCell::FloorCell()
{
    type = None;
}

FloorCell::FloorCell(FloorCellType type)
{
    this->type = type;
}

FloorCellType FloorCell::getType()
{
    return type;
}

FloorCell::~FloorCell()
{
}


#endif