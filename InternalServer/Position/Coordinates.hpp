#ifndef Coordinates_hpp_
#define Coordinates_hpp_
#include "Vector2d.hpp"

class Coordinates
{
public:
    double x;
    double y;
    int z;
    Coordinates(double x, double y, int z);
    Coordinates();
    Coordinates operator + (const Coordinates other);
    Coordinates operator + (const Vector2d other);
    Coordinates operator - (const Coordinates other);
    Coordinates operator - (const Vector2d other);
    bool operator == (const Coordinates& other);
    bool operator != (const Coordinates& other);
};

Coordinates::Coordinates(double x, double y, int z = 0)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Coordinates::Coordinates()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Coordinates Coordinates::operator + (const Coordinates other)
{
    return Coordinates(x + other.x, y + other.y, z + other.z);
}

Coordinates Coordinates::operator + (const Vector2d other)
{
    return Coordinates(x + other.x, y + other.y, z);
}

Coordinates Coordinates::operator - (const Coordinates other)
{
    return Coordinates(x - other.x, y - other.y, z - other.z);
}

Coordinates Coordinates::operator - (const Vector2d other)
{
    return Coordinates(x - other.x, y - other.y, z);
}

bool Coordinates::operator == (const Coordinates& other)
{
    return x == other.x && y == other.y && z == other.z;
}

bool Coordinates::operator != (const Coordinates& other)
{
    return x != other.x || y != other.y || z != other.z;
}

#endif
