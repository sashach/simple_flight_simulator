#include "waypoint.h"

WayPoint::WayPoint():
    x(0),
    y(0),
    z(0),
    passed(false),
    mandatory(true)
{

}

WayPoint::WayPoint(const int _x, const int _y, const int _z):
    x(_x),
    y(_y),
    z(_z),
    passed(false),
    mandatory(true)
{

}

WayPoint::WayPoint(const WayPoint & other):
    x(other.x),
    y(other.y),
    z(other.z),
    passed(other.passed),
    mandatory(other.mandatory),
    name(other.name)
{

}

const WayPoint & WayPoint::operator = (const WayPoint & other)
{
    if(this != &other)
    {
        x = other.x;
        y = other.y;
        z = other.z;
        passed = other.passed;
        mandatory = other.mandatory;
        name = other.name;
    }
    return *this;
}

int WayPoint::getX() const
{
    return x;
}

int WayPoint::getY() const
{
    return y;
}

int WayPoint::getZ() const
{
    return z;
}

bool WayPoint::isPassed() const
{
    return passed;
}

bool WayPoint::isMandatory() const
{
    return mandatory;
}

void WayPoint::setPassed(const bool _passed)
{
    passed = _passed;
}

const QString &WayPoint::getName() const
{
    return name;
}

void WayPoint::setName(const std::string & _name)
{
    name = QString(_name.c_str());
}
