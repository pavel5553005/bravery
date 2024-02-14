#ifndef Camera_hpp_
#define Camera_hpp_
#include "Vector2d.hpp"
#include "ObjOnLayout/ObjOnLayout.hpp"
#include "Map/Map.hpp"
#include "Coordinates.hpp"

class Camera
{
private:
    Coordinates pos;
    Vector2d size;
    ObjOnLayout* followObj;
    
public:
    Camera();
    Camera(Coordinates pos, Vector2d size, ObjOnLayout* followObj);
    ~Camera();
};

Camera::Camera(Coordinates pos, Vector2d size, ObjOnLayout* followObj)
{
    this->followObj = followObj;
    this->pos = pos;
    this->size = size;
}

Camera::Camera()
{
}

Camera::~Camera()
{
}

#endif