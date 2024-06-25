#ifndef Player_hpp_
#define Player_hpp_
#include "GameCharacter.hpp"

class Player : public GameCharacter
{
private:
public:
    Player(const Coordinates pos, const Vector2d size, const std::string name);
    ~Player();
};

Player::Player(const Coordinates pos, const Vector2d size, const std::string name) : GameCharacter(pos, size, name) { }

Player::~Player() { }

#endif