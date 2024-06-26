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
public:
    NPC();
    NPC(const Coordinates pos, const Vector2d size);
    NPC(const Coordinates pos, const Vector2d size, const std::string name);

    ~NPC();
};

NPC::NPC()
{
    name = generateName();
}

NPC::NPC(const Coordinates pos, const Vector2d size) : GameCharacter(pos, size, NPC::generateName()) { }

NPC::NPC(const Coordinates pos, const Vector2d size, const std::string name) : GameCharacter(pos, size, name) { }

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
    BaS.console.log(name);
    return name;
}

NPC::~NPC()
{
}


#endif