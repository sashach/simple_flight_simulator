#include "flight.h"

Flight::Flight(QObject *parent) :
    QObject(parent),
    x(0),
    y(0),
    h(0)
{
    wayPoints.reserve(MAX_FLIGHT_POINTS);
}

Flight::Flight(const Flight &other): QObject(other.parent())
{
    wayPoints = other.wayPoints;
    x = other.x;
    y = other.y;
    h = other.h;
}

const Flight & Flight::operator = (const Flight & other)
{
    if(this != &other)
    {
        wayPoints.clear();
        wayPoints = other.wayPoints;
        x = other.x;
        y = other.y;
        h = other.h;
    }
    return *this;
}

void Flight::addWayPoint(const WayPoint & wayPoint)
{
    wayPoints.push_back(wayPoint);
}

const QVector<WayPoint> & Flight::getWayPoints() const
{
    return wayPoints;
}

void Flight::updateFlightPosition(const int _x, const int _y, const int _h)
{
    x = _x;
    y = _y;
    h = _h;
}

int Flight::getX() const
{
    return x;
}

int Flight::getY() const
{
    return y;
}

int Flight::getH() const
{
    return h;
}
