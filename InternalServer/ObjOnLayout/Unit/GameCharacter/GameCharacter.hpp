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
    GameCharacter(const Coordinates pos, const Vector2d size, const std::string name);

    const std::string& getName() const { return name; }

    void setName(const std::string name) { this->name = name; }

    ~GameCharacter();
};

GameCharacter::GameCharacter() { }

GameCharacter::GameCharacter(const Coordinates pos, const Vector2d size, const std::string name) :
Unit(pos, size), name(name) { }

GameCharacter::~GameCharacter() { }


#endif