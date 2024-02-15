#ifndef Vector2d_hpp_
#define Vector2d_hpp_
#include <math.h>

class Vector2d
{
private:
    double x;
    double y;
public:
    Vector2d();
    Vector2d(double x, double y);
    Vector2d(double length, int angle);
    double getX();
    double getY();
    double getLength();
    double getAngle();
    ~Vector2d();
};

Vector2d::Vector2d()
{
    x = 0;
    y = 0;
}

Vector2d::Vector2d(double x, double y)
{
    this->x = x;
    this->y = y;
}

Vector2d::Vector2d(double length, int angle)
{
    this->x = length * cos(angle * M_PI / 180);
    this->y = length * -sin(angle * M_PI / 180);
}

double Vector2d::getX()
{
    return x;
}

double Vector2d::getY()
{
    return y;
}

double Vector2d::getLength()
{
    return sqrt(x * x + y * y);
}

double Vector2d::getAngle()
{
    return atan2(y, x) * 180 / M_PI;
}

Vector2d::~Vector2d()
{
}

#endif