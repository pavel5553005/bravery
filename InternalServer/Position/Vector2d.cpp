#include "Vector2d.hpp"
#include "Coordinates.hpp"

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

Vector2d::Vector2d(Coordinates pos)
{
    this->x = pos.x;
    this->y = pos.y;
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
    return *this;
}