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
    
    const Type type;

    union
    {
        ObjMove objMove;
        ObjSpawn objSpawn;
        bool nullEvent;
    };
    
    Event(const Type type);
};

Event::Event(const Type type) : type(type) { }

#endif