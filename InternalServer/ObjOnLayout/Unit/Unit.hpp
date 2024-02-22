#ifndef Unit_hpp_
#define Unit_hpp_
#include "../ObjOnLayout.hpp"

class Unit : public ObjOnLayout
{
private:
    unsigned int hp;
    unsigned int maxHp;
    double speed;
public:
    Unit(Coordinates pos, Vector2d size, Layout& layout);

    void setHp(unsigned int hp);
    void setMaxHp(unsigned int maxHp);

    unsigned int getHp();
    unsigned int getMaxHp();

    void move(int angle);
    void event(Event event);

    ~Unit();
};

Unit::Unit(Coordinates pos, Vector2d size, Layout& layout) : ObjOnLayout(pos, size, layout)
{
    hp = 100;
    maxHp = 100;
    speed = 0.3;
}

void Unit::setHp(unsigned int hp) { this->hp = hp; }

void Unit::setMaxHp(unsigned int maxHp) { this->maxHp = maxHp; }

unsigned int Unit::getHp() { return hp; }

unsigned int Unit::getMaxHp() { return maxHp; }

void Unit::move(int angle)
{
    Unit::setPos(Coordinates(Unit::getPos().x + cos(angle * M_PI / 180) * speed, Unit::getPos().y - sin(angle * M_PI / 180) * speed));
}

void Unit::event(Event event)
{
    printf("Unit event\n");
}

Unit::~Unit()
{
}


#endif