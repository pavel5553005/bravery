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

    void event(Event event);

    ~Animal();
};

Animal::Animal(Coordinates pos, Vector2d size, Layout& layout) : Unit(pos, size, layout)
{
    timeBeforeMove = 0;
}

void Animal::event(Event event)
{
    if (event.type == Event::Type::Tick)
    {
        if (isPathEmpty())
        {
            timeBeforeMove = rand() % 60;
            timeBeforeMove--;
            if (timeBeforeMove == 0)
            {
                while (true)
                {
                    int x = rand() % 100;
                    int y = rand() % 100;
                    if (layout->getMap()->getCell(x, y, getPos().z)->getWallType() == MapCell::WallType::None 
                    and (x != getPos().x or y != getPos().y)
                    and (x - getPos().x) * (x - getPos().x) + (y - getPos().y) * (y - getPos().y) < 100)
                    {
                        addPath(Coordinates(x, y));
                        debuger.consoleLog("add path");

                        break;
                    }
                }
            }
        }
        walk();
    }
}

Animal::~Animal() { }

#endif