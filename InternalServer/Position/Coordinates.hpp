#ifndef Coordinates_hpp_
#define Coordinates_hpp_
#include "Vector2d.hpp"

class Coordinates
{
public:
    double x;
    double y;
    int z;
    Coordinates(const double x, const double y, const int z);
    Coordinates();
    Coordinates operator + (const Coordinates& other) const;
    Coordinates operator + (const Vector2d& other) const;
    Coordinates operator - (const Coordinates& other) const;
    Coordinates operator - (const Vector2d& other) const;
    bool operator == (const Coordinates& other) const;
    bool operator != (const Coordinates& other) const;
    bool operator < (const Coordinates& other) const;
    bool operator > (const Coordinates& other) const;
    bool operator <= (const Coordinates& other) const;
    bool operator >= (const Coordinates& other) const;
};

Coordinates::Coordinates(double x, double y, int z) : x(x), y(y), z(z) { }

Coordinates::Coordinates() : x(0), y(0), z(0) { }

Coordinates Coordinates::operator + (const Coordinates& other) const { return Coordinates(x + other.x, y + other.y, z + other.z); }

Coordinates Coordinates::operator + (const Vector2d& other) const { return Coordinates(x + other.x, y + other.y, z); }

Coordinates Coordinates::operator - (const Coordinates& other) const { return Coordinates(x - other.x, y - other.y, z - other.z); }

Coordinates Coordinates::operator - (const Vector2d& other) const { return Coordinates(x - other.x, y - other.y, z); }

bool Coordinates::operator == (const Coordinates& other) const { return x == other.x and y == other.y and z == other.z; }

bool Coordinates::operator != (const Coordinates& other) const { return x != other.x or y != other.y or z != other.z; }

bool Coordinates::operator < (const Coordinates& other) const { return x < other.x and y < other.y and z < other.z; }

bool Coordinates::operator > (const Coordinates& other) const { return x > other.x and y > other.y and z > other.z; }

bool Coordinates::operator <= (const Coordinates& other) const { return x <= other.x and y <= other.y and z <= other.z; }

bool Coordinates::operator >= (const Coordinates& other) const { return x >= other.x and y >= other.y and z >= other.z; }

#endif
