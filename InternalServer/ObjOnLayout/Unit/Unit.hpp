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
    void walk(Event event);
public:
    Unit();
    Unit(const Coordinates pos, const Vector2d size);

    void setHp(int hp);
    void setMaxHp(unsigned int maxHp) { this->maxHp = maxHp; }
    void setSpeed(double speed) { this->speed = speed; }

    int getHp() const { return hp; }
    int getMaxHp() const { return maxHp; }
    double getSpeed() const { return speed; }
    bool isPathEmpty() const { return pathList.empty(); }

    void addPath(const Coordinates pos) { pathList.push_back(pos); }
    void deletePath(const Coordinates pos) { pathList.remove(pos); }
    void move(const int angle);
    void move(const Coordinates pos);
    ~Unit();
};

Unit::Unit() {}

Unit::Unit(const Coordinates pos, const Vector2d size) : ObjOnLayout(pos, size)
{
    hp = 100;
    maxHp = 100;
    speed = 0.1;
    handler.addListener(std::bind(&Unit::walk, this, std::placeholders::_1), Event::Type::Tick);
}

void Unit::setHp(int hp)
{
    if (hp > int(maxHp)) hp = maxHp;
    if (hp < 0) hp = 0;
    this->hp = hp;
}

void Unit::move(int angle)
{
    if (hp <= 0) return;
    Unit::setPos(Coordinates(Unit::getPos().x + cos(angle * M_PI / 180) * speed, Unit::getPos().y - sin(angle * M_PI / 180) * speed, Unit::getPos().z));
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
        Unit::setPos(Coordinates(Unit::getPos().x + cos(angle * M_PI / 180) * speed, Unit::getPos().y + sin(angle * M_PI / 180) * speed, Unit::getPos().z));
    }
}

void Unit::walk(Event event)
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

Unit::~Unit() { }


#endif