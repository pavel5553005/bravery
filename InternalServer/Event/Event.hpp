#ifndef Event_hpp_
#define Event_hpp_
#include "../ObjOnLayout/ObjOnLayout.hpp"



class Event
{
public:
    struct ObjMove
    {
        ObjOnLayout* obj;
        Coordinates start;
        Coordinates end;
    };
    
    struct ObjSpawn
    {
        ObjOnLayout* obj;
        Coordinates pos;
    };

    enum class Type {
        TestEvent,
        ObjMove,
        ObjSpawn
    };
    
    Type type;

    union
    {
        ObjMove objMove;
        ObjSpawn objSpawn;
        bool nullEvent;
    };
    
    Event();
};

Event::Event()
{

}

#endif