#include "waypointpo.h"

WayPointPO::WayPointPO()
{

}

WayPointPO::WayPointPO(const int x, const int y, const int h, const bool _passed, const std::string & _name):
    coordinates(x, y, h),
    passed(_passed),
    name(_name.c_str())
{
    labelRow2 = QString::number(coordinates.getH());
}

const Point3d & WayPointPO::getCoordinates() const
{
    return coordinates;
}

bool WayPointPO::isPassed() const
{
    return passed;
}

const QString & WayPointPO::getName() const
{
    return name;
}

const QString & WayPointPO::getLabelString2() const
{
    return labelRow2;
}
