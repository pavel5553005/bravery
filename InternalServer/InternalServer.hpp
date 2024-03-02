#ifndef InternalServer_hpp_
#define InternalServer_hpp_
#include "../Header.hpp"

class InternalServer
{
private:
    Layout layout;
public:
    InternalServer();

    Layout* getLayout();

    void tick();

    ~InternalServer();
};

InternalServer::InternalServer() {}

Layout* InternalServer::getLayout() { return &layout; }

void InternalServer::tick()
{
    layout.tick();
}

InternalServer::~InternalServer() {}

#endif