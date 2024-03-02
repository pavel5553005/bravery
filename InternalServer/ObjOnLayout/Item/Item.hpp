#ifndef Item_hpp_
#define Item_hpp_
#include "../ObjOnLayout.hpp"

class Item : public ObjOnLayout
{
public:
    enum class Type {
        Eat
    };
private:
    unsigned int count;
    Type type;
public:
    Item(Coordinates pos, Vector2d size, Layout& layout, Type type, unsigned int count = 1);
    Item(ObjOnLayout& obj, Type type, unsigned int count = 1);

    unsigned int getCount();
    Type getType();
    
    void setCount(unsigned int count);

    ~Item();
};

Item::Item(Coordinates pos, Vector2d size, Layout& layout, Type type, unsigned int count) : ObjOnLayout(pos, size, layout)
{
    this->type = type;
    this->count = count;
}

Item::Item(ObjOnLayout& obj, Type type, unsigned int count) : ObjOnLayout(obj)
{
    this->type = type;
    this->count = count;
}

Item::~Item()
{
}



#endif