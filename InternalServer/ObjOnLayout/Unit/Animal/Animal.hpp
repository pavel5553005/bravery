#ifndef Animal_hpp_
#define Animal_hpp_
#include "../Unit.hpp"
#include <random>

class Animal : public Unit
{
private:
    int timeBeforeMove;
public:
    Animal(const Coordinates pos, const Vector2d size);

    ~Animal();
};

Animal::Animal(const Coordinates pos, const Vector2d size) : Unit(pos, size), timeBeforeMove(0) { }

Animal::~Animal() { }

#endif