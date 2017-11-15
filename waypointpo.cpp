#include "waypointpo.h"

WayPointPO::WayPointPO()
{

}

WayPointPO::WayPointPO(const int x, const int y, const bool _passed, const std::string & _name):
    screenX(x),
    screenY(y),
    passed(_passed),
    name(_name.c_str())
{

}

int WayPointPO::getX() const
{
    return screenX;
}

int WayPointPO::getY() const
{
    return screenY;
}

bool WayPointPO::isPassed() const
{
    return passed;
}

const QString & WayPointPO::getName() const
{
    return name;
}
