#ifndef Event_hpp_
#define Event_hpp_
#include "../ObjOnLayout/ObjOnLayout.hpp"

class Event
{
public:
    
    struct ObjSpawn
    {
        ObjOnLayout* obj;
        Coordinates pos;
    };

    struct ObjMove
    {
        ObjOnLayout* obj;
        Coordinates pos;
    };

    enum class Type {
        ObjMove,
        TestEvent,
        ObjSpawn,
        Tick
    };
    
    Type type;

    union
    {
        ObjMove objMove;
        ObjSpawn objSpawn;
        bool nullEvent;
    };
    
    Event(Type type);
};

Event::Event(Type type)
{
    this->type = type;
}

#endif