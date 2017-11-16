#include "flight.h"
#include "constants.h"

Flight::Flight(QObject *parent) :
    QObject(parent)
{
    wayPoints.reserve(MAX_FLIGHT_POINTS);
}

Flight::Flight(const Flight &other):
    QObject(other.parent())
{
    wayPoints = other.wayPoints;
    coordinates = other.coordinates;
}

const Flight & Flight::operator = (const Flight & other)
{
    if(this != &other)
    {
        wayPoints.clear();
        wayPoints = other.wayPoints;
        coordinates = other.coordinates;
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

void Flight::updateCoordinates(const int x, const int y, const int h)
{
    coordinates.update(x, y, h);
}

void Flight::updateCoordinates(const Point3d & coord)
{
    coordinates = coord;
}

const Point3d & Flight::getCoordinates() const
{
    return coordinates;
}
