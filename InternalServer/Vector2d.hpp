#ifndef Vector2d_hpp_
#define Vector2d_hpp_
#include <math.h>
#include <iostream>

class Vector2d
{
public:
    double x;
    double y;
    Vector2d();
    Vector2d(double x, double y);
    Vector2d(double length, int angle);
    double getLength();
    double getAngle();
    Vector2d& operator=(const Vector2d& other);
};

Vector2d::Vector2d()
{
    x = 0;
    y = 0;
    std::cout << "Vector2d:" << x << " " << y << std::endl;
}

Vector2d::Vector2d(double x, double y)
{
    this->x = x;
    this->y = y;
    std::cout << "Vector2d:" << x << " " << y << std::endl;
}

Vector2d::Vector2d(double length, int angle)
{
    this->x = length * cos(angle * M_PI / 180);
    this->y = length * -sin(angle * M_PI / 180);
}


double Vector2d::getLength()
{
    return sqrt(x * x + y * y);
}

double Vector2d::getAngle()
{
    return atan2(y, x) * 180 / M_PI;
}

Vector2d& Vector2d::operator=(const Vector2d& other)
{
    if (true)
    {
        x = other.x;
        y = other.y;
    }
    std::cout << "Vector2d = :" << x << " " << y << std::endl;
    return *this;
}

#endif