#include "waypoint.h"

WayPoint::WayPoint():
    passed(false),
    mandatory(true)
{

}

WayPoint::WayPoint(const int x, const int y, const int h):
    coordinates(x, y, h),
    passed(false),
    mandatory(true)
{

}

WayPoint::WayPoint(const WayPoint & other):
    coordinates(other.coordinates),
    passed(other.passed),
    mandatory(other.mandatory),
    name(other.name)
{

}

const WayPoint & WayPoint::operator = (const WayPoint & other)
{
    if(this != &other)
    {
        coordinates = other.coordinates;
        passed = other.passed;
        mandatory = other.mandatory;
        name = other.name;
    }
    return *this;
}

const Point3d & WayPoint::getCoordinates() const
{
    return coordinates;
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

const std::string & WayPoint::getName() const
{
    return name;
}

void WayPoint::setName(const std::string & _name)
{
    name = _name;
}
