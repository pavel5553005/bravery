#ifndef GameCharacter_hpp_
#define GameCharacter_hpp_
#include "../Unit.hpp"
#include <string>

class GameCharacter : public Unit
{
private:
protected:
    std::string name;
public:
    GameCharacter();
    GameCharacter(Coordinates pos, Vector2d size, Layout& layout, std::string name);
    GameCharacter(Unit& unit, std::string name);

    std::string getName();

    void setName(std::string name);

    ~GameCharacter();
};

GameCharacter::GameCharacter() { }

GameCharacter::GameCharacter(Coordinates pos, Vector2d size, Layout& layout, std::string name)
: Unit(pos, size, layout) { this->name = name; }

GameCharacter::GameCharacter(Unit& unit, std::string name)
: Unit(unit), name(name) { }

std::string GameCharacter::getName() { return name; }

void GameCharacter::setName(std::string name) { this->name = name; }

GameCharacter::~GameCharacter() { }


#endif