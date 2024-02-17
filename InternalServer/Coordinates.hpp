#ifndef Coordinates_hpp_
#define Coordinates_hpp_

class Coordinates
{
public:
    double x;
    double y;
    int z;
    Coordinates(double x, double y, int z);
    Coordinates();
    Coordinates operator + (Coordinates other);
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

Coordinates Coordinates::operator + (Coordinates other)
{
    return Coordinates(x + other.x, y + other.y, z + other.z);
}

#endif
