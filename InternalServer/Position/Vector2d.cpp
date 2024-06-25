#include "Vector2d.hpp"
#include "Coordinates.hpp"

Vector2d::Vector2d() : x(0), y(0) { }

Vector2d::Vector2d(const double x, const double y) : x(x), y(y) { }
Vector2d::Vector2d(const Coordinates pos)  : x(pos.x), y(pos.y) { }

double Vector2d::getLength() { return sqrt(x * x + y * y); }

double Vector2d::getAngle() { return atan2(y, x) * 180 / M_PI; }