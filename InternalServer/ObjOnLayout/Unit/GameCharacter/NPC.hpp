#ifndef NPC_hpp_
#define NPC_hpp_
#include "GameCharacter.hpp"
#include <random>
#include <iostream>

class NPC : public GameCharacter
{
private:
    std::string generateName();
    bool isVowel(char c);
    Coordinates targetPos;
public:
    NPC();
    NPC(Coordinates pos, Vector2d size, Layout& layout);
    NPC(Coordinates pos, Vector2d size, Layout& layout, std::string name);

    void walk(Coordinates pos);
    void event(Event event);

    ~NPC();
};

NPC::NPC()
{
    name = generateName();
}

NPC::NPC(Coordinates pos, Vector2d size, Layout& layout) : GameCharacter(pos, size, layout, NPC::generateName()) { }

NPC::NPC(Coordinates pos, Vector2d size, Layout& layout, std::string name) : GameCharacter(pos, size, layout, name) { }

void NPC::walk(Coordinates pos) { targetPos = pos; }

void NPC::event(Event event)
{
    if (event.type == Event::Type::Tick)
    {
        if (int(NPC::getPos().y) == int(targetPos.y) && int(NPC::getPos().x) == int(targetPos.x))
        {
            NPC::setPos(targetPos);
        }
        else if (NPC::getPos() != targetPos)
        {
            NPC::move(targetPos);
        }
    }
}

bool NPC::isVowel(char c)
{
    for (auto i : "AEIOUaeiou")
    {
        if (i == c)
        {
            return true;
        }
    }
    return false;
}

std::string NPC::generateName()
{
    std::string name;
    int length = rand() % 6 + 4;
    for (int i = 0; i < length; i++)
    {
        if (i % 2 == 0)
        {
            char r = rand() % 26 + 'a';
            while (isVowel(r))
            {
                r = rand() % 26 + 'a';
            }
            name += r;
        }
        else
        {
            char r = rand() % 26 + 'a';
            while (!isVowel(r))
            {
                r = rand() % 26 + 'a';
            }
            name += r;
        }
    }
    name[0] = toupper(name[0]);
    std::cout << name << std::endl;
    return name;
}

NPC::~NPC()
{
}


#endif