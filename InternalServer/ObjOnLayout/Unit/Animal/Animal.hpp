#ifndef Animal_hpp_
#define Animal_hpp_
#include "../Unit.hpp"

class Animal : public Unit
{
private:

public:
    Animal(Coordinates pos, Vector2d size, Layout& layout);
    ~Animal();
};

Animal::Animal(Coordinates pos, Vector2d size, Layout& layout) : Unit(pos, size, layout) {}

Animal::~Animal() { }

#endif