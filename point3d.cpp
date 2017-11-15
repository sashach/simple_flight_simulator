#include "point3d.h"

Point3d::Point3d():
    x(0),
    y(0),
    h(0)
{

}

Point3d::Point3d(const int _x, const int _y, const int _h):
    x(_x),
    y(_y),
    h(_h)
{

}

void Point3d::update(const int _x, const int _y, const int _h)
{
    x = _x;
    y = _y;
    h = _h;
}

const Point3d & Point3d::operator = (const Point3d &other)
{
    if(this != &other)
    {
        x = other.x;
        y = other.y;
        h = other.h;
    }
    return *this;
}

int Point3d::getX() const
{
    return x;
}

int Point3d::getY() const
{
    return y;
}

int Point3d::getH() const
{
    return h;
}
