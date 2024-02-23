#ifndef Player_hpp_
#define Player_hpp_
#include "GameCharacter.hpp"

class Player : public GameCharacter
{
private:
public:
    Player(Coordinates pos, Vector2d size, Layout& layout, std::string name);
    Player(Unit& unit, std::string name);
    ~Player();
};

Player::Player(Coordinates pos, Vector2d size, Layout& layout, std::string name) : GameCharacter(pos, size, layout, name) { }

Player::Player(Unit& unit, std::string name) : GameCharacter(unit, name) { }

Player::~Player() { }

#endif