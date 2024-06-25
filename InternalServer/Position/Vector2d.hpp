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
    Vector2d(const Coordinates pos);
    Vector2d(const double x, const double y);

    double getLength();
    double getAngle();
    
};

#endif