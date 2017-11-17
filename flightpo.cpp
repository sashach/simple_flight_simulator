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
    wayPoints(other.wayPoints),
    aircraftId(other.aircraftId),
    labelCoordinates(other.labelCoordinates),
    simulatorTimeDiff(other.simulatorTimeDiff)
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
        aircraftId = other.aircraftId;
        labelCoordinates = other.labelCoordinates;
        simulatorTimeDiff = other.simulatorTimeDiff;
    }
    return *this;
}

void FlightPO::updateFlight(const Flight & flight)
{
    relativeCoordinates = flight.getCoordinates();
    relativeWayPoints = flight.getWayPoints();
    aircraftId = QString(flight.getAircraftId().c_str());

    labelCoordinates = QString::number(relativeCoordinates.getX()) + ":"
            + QString::number(relativeCoordinates.getY()) + ":"
            + QString::number(relativeCoordinates.getH());

    switch(flight.getClimbDescent())
    {
    case Flight::CLIMB_DESCENT_CLIMB:
        labelCoordinates += QChar(0x2191);
        break;

    case Flight::CLIMB_DESCENT_DESCENT:
        labelCoordinates += QChar (0x2193);
        break;
    }

    simulatorTimeDiff = QString::number(flight.getSimulatorTimeDiff());
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
                    it->getCoordinates().getH(),
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

const QString & FlightPO::getAircraftId() const
{
    return aircraftId;
}

const QString & FlightPO::getLabelCoordinates() const
{
    return labelCoordinates;
}

const QString & FlightPO::getSimulatorTimeDiff() const
{
    return simulatorTimeDiff;
}
