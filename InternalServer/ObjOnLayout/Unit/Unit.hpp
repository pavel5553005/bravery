#ifndef Unit_hpp_
#define Unit_hpp_
#include "../ObjOnLayout.hpp"
#include "../../Event/Event.hpp"
#include <iostream>


class Unit : public ObjOnLayout
{
private:
    unsigned int hp;
    unsigned int maxHp;
    double speed;
    std::list<Coordinates> pathList;
protected:
    void walk();
public:
    Unit();
    Unit(Coordinates pos, Vector2d size, Layout& layout);

    void setHp(unsigned int hp);
    void setMaxHp(unsigned int maxHp);
    void setSpeed(double speed);

    unsigned int getHp();
    unsigned int getMaxHp();
    double getSpeed();
    bool isPathEmpty();

    void addPath(Coordinates pos);
    void deletePath();
    void move(int angle);
    void move(Coordinates pos);
    void event(Event event);

    ~Unit();
};

Unit::Unit() {}

Unit::Unit(Coordinates pos, Vector2d size, Layout& layout) : ObjOnLayout(pos, size, layout)
{
    hp = 100;
    maxHp = 100;
    speed = 0.1;
}

void Unit::setHp(unsigned int hp) { this->hp = hp; }

void Unit::setMaxHp(unsigned int maxHp) { this->maxHp = maxHp; }

void Unit::setSpeed(double speed) { this->speed = speed; }

unsigned int Unit::getHp() { return hp; }

unsigned int Unit::getMaxHp() { return maxHp; }

double Unit::getSpeed() { return speed; }

bool Unit::isPathEmpty() { return pathList.empty(); }

void Unit::addPath(Coordinates pos) { pathList.push_back(pos); }

void Unit::deletePath() { pathList.clear(); }

void Unit::move(int angle)
{
    Unit::setPos(Coordinates(Unit::getPos().x + cos(angle * M_PI / 180) * speed, Unit::getPos().y - sin(angle * M_PI / 180) * speed));
}

void Unit::move(Coordinates pos)
{
    if ((pos.x - Unit::getPos().x) * (pos.x - Unit::getPos().x) + (pos.y - Unit::getPos().y) * (pos.y - Unit::getPos().y) < speed * speed)
    {
        Unit::setPos(pos);
    }
    else
    {
        int angle = atan2((pos.y - Unit::getPos().y), (pos.x - Unit::getPos().x)) * 180 / M_PI;
        Unit::setPos(Coordinates(Unit::getPos().x + cos(angle * M_PI / 180) * speed, Unit::getPos().y + sin(angle * M_PI / 180) * speed));
    }
}

void Unit::walk()
{
    if (!pathList.empty())
    {
        if (Unit::getPos() == pathList.front())
        {
            pathList.pop_front();
        }
        if (!pathList.empty())
        {
            Unit::move(pathList.front());
        }
    }
}

void Unit::event(Event event)
{
    if (event.type == Event::Type::Tick)
    {
        Unit::walk();
    }
}

Unit::~Unit()
{
}


#endif