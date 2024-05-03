#ifndef Animal_hpp_
#define Animal_hpp_
#include "../Unit.hpp"
#include <random>

class Animal : public Unit
{
private:
    int timeBeforeMove;
public:
    Animal(Coordinates pos, Vector2d size, Layout& layout);

    ~Animal();
};

Animal::Animal(Coordinates pos, Vector2d size, Layout& layout) : Unit(pos, size, layout)
{
    timeBeforeMove = 0;
}

Animal::~Animal() { }

#endif