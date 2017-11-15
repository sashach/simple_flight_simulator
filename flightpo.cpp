#include "flightpo.h"
#include "flight.h"
#include "constants.h"
#include "screencoordinatescalculator.h"

FlightPO::FlightPO(QObject *parent) :
    QObject(parent),
    screenX(0),
    screenY(0)
{
    wayPoints.reserve(MAX_FLIGHT_POINTS);
}

FlightPO::FlightPO(const FlightPO &other):
    QObject(other.parent()),
    relativeCoordinates(other.relativeCoordinates),
    relativeWayPoints(other.relativeWayPoints),
    screenX(other.screenX),
    screenY(other.screenY),
    wayPoints(other.wayPoints)
{
}

const FlightPO & FlightPO::operator = (const FlightPO & other)
{
    if(this != &other)
    {
        relativeCoordinates = other.relativeCoordinates;
        relativeWayPoints = other.relativeWayPoints;
        screenX = other.screenX;
        screenY = other.screenY;
        wayPoints = other.wayPoints;
    }
    return *this;
}

void FlightPO::updateFlight(const Flight & flight)
{
    relativeCoordinates = flight.getCoordinates();
    relativeWayPoints = flight.getWayPoints();
}

void FlightPO::updateScreenCoordinates(const ScreenCoordinatesCalculator & calculator)
{
    screenX = calculator.getScreenX(relativeCoordinates.getX());
    screenY = calculator.getScreenY(relativeCoordinates.getY());

    wayPoints.clear();
    for(auto it = relativeWayPoints.begin(); it != relativeWayPoints.end(); ++it)
    {
        WayPointPO wayPoint(
                    calculator.getScreenX(it->getCoordinates().getX()),
                    calculator.getScreenY(it->getCoordinates().getY()),
                    it->isPassed(),
                    it->getName()
                    );
        wayPoints.push_back(wayPoint);
    }
}

int FlightPO::getX() const
{
    return screenX;
}

int FlightPO::getY() const
{
    return screenY;
}

const QVector<WayPointPO> & FlightPO::getWayPoints() const
{
    return wayPoints;
}
