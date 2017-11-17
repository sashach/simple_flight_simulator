#include "flight.h"
#include "constants.h"


Flight::Flight(const std::string &_aircraftId, QObject *parent) :
    QObject(parent),
    speed(GRID_SIZE),
    aircraftId(_aircraftId),
    simulatorTimeDiff(0.0),
    climbDescent(CLIMB_DESCENT_NONE)
{
    wayPoints.reserve(MAX_FLIGHT_POINTS);
}

Flight::Flight(const Flight &other):
    QObject(other.parent())
{
    wayPoints = other.wayPoints;
    coordinates = other.coordinates;
    speed = other.speed;
    lastUpdateTime = other.lastUpdateTime;
    aircraftId = other.aircraftId;
    simulatorTimeDiff = other.simulatorTimeDiff;
    climbDescent = other.climbDescent;
}

const Flight & Flight::operator = (const Flight & other)
{
    if(this != &other)
    {
        wayPoints.clear();
        wayPoints = other.wayPoints;
        coordinates = other.coordinates;
        speed = other.speed;
        lastUpdateTime = other.lastUpdateTime;
        aircraftId = other.aircraftId;
        simulatorTimeDiff = other.simulatorTimeDiff;
        climbDescent = other.climbDescent;
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

QVector<WayPoint> & Flight::getWayPoints()
{
    return wayPoints;
}

void Flight::updateCoordinates(const int x, const int y, const int h)
{
    updateCoordinates(Point3d(x, y, h));
}

void Flight::updateCoordinates(const Point3d & coord)
{
    if(coord.getH() > coordinates.getH())
    {
        climbDescent = CLIMB_DESCENT_CLIMB;
    }
    else if (coord.getH() < coordinates.getH())
    {
        climbDescent = CLIMB_DESCENT_DESCENT;
    }
    else
    {
        climbDescent = CLIMB_DESCENT_NONE;
    }

    coordinates = coord;
    lastUpdateTime = QDateTime::currentDateTime();
}

const Point3d & Flight::getCoordinates() const
{
    return coordinates;
}

int Flight::getSpeed() const
{
    return speed;
}

QDateTime Flight::getLastUpdateTime()
{
    return lastUpdateTime;
}

const std::string & Flight::getAircraftId() const
{
    return aircraftId;
}

void Flight::setSimulatorTimeDiff(const double timeDiff)
{
    simulatorTimeDiff = timeDiff;
}

double Flight::getSimulatorTimeDiff() const
{
    return simulatorTimeDiff;
}

int Flight::getClimbDescent() const
{
    return climbDescent;
}
