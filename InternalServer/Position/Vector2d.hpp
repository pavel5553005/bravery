#ifndef Vector2d_hpp_
#define Vector2d_hpp_
#include <math.h>
#include <iostream>

class Coordinates;

class Vector2d
{
public:
    double x;
    double y;
    Vector2d();
    Vector2d(Coordinates pos);
    Vector2d(double x, double y);

    double getLength();
    double getAngle();
    
    Vector2d& operator=(const Vector2d& other);

};

#endif