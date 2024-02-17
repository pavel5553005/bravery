#ifndef Event_hpp_
#define Event_hpp_



class Event
{
public:
    enum class Type {
        TestEvent,
        ObjMove
    };
    
    Type type;
    Event(Type type);
};

Event::Event(Type type)
{
    this->type = type;
}


#endif