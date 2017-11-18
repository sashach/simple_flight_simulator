#include "flightpo.h"
#include "flight.h"
#include "constants.h"
#include "screencoordinatescalculator.h"

FlightPO::FlightPO(const int _id, QObject *parent) :
    QObject(parent),
    id(_id),
    screenX(0),
    screenY(0),
    altitudeInFeet(false),
    climbDescent(Flight::CLIMB_DESCENT_NONE)
{
    wayPoints.reserve(MAX_FLIGHT_POINTS);
}

FlightPO::FlightPO(const FlightPO &other):
    QObject(other.parent()),
    id(other.id),
    relativeCoordinates(other.relativeCoordinates),
    relativeWayPoints(other.relativeWayPoints),
    screenX(other.screenX),
    screenY(other.screenY),
    wayPoints(other.wayPoints),
    aircraftId(other.aircraftId),
    labelCoordinates(other.labelCoordinates),
    simulatorTimeDiff(other.simulatorTimeDiff),
    altitudeInFeet(other.altitudeInFeet),
    climbDescent(other.climbDescent)
{
}

const FlightPO & FlightPO::operator = (const FlightPO & other)
{
    if(this != &other)
    {
        id = other.id;
        relativeCoordinates = other.relativeCoordinates;
        relativeWayPoints = other.relativeWayPoints;
        screenX = other.screenX;
        screenY = other.screenY;
        wayPoints = other.wayPoints;
        aircraftId = other.aircraftId;
        labelCoordinates = other.labelCoordinates;
        simulatorTimeDiff = other.simulatorTimeDiff;
        altitudeInFeet = other.altitudeInFeet;
        climbDescent = other.climbDescent;
    }
    return *this;
}

void FlightPO::updateFlight(const Flight & flight)
{
    relativeCoordinates = flight.getCoordinates();
    relativeWayPoints = flight.getWayPoints();
    aircraftId = QString(flight.getAircraftId().c_str());
    climbDescent = flight.getClimbDescent();

    updateLabelCoordinates();

    simulatorTimeDiff = QString::number(flight.getSimulatorTimeDiff()/1000.0);
}

void FlightPO::updateLabelCoordinates()
{
    labelCoordinates = QString::number(relativeCoordinates.getX()) + ":"
            + QString::number(relativeCoordinates.getY()) + ":";

    if(altitudeInFeet)
    {
        labelCoordinates += "F" + QString::number(0.328084 * relativeCoordinates.getH());
    }
    else
    {
        labelCoordinates += "M" + QString::number(relativeCoordinates.getH());
    }

    switch(climbDescent)
    {
    case Flight::CLIMB_DESCENT_CLIMB:
        labelCoordinates += QChar(0x2191);
        break;

    case Flight::CLIMB_DESCENT_DESCENT:
        labelCoordinates += QChar (0x2193);
        break;
    }
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
                    it->isMandatory(),
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

void FlightPO::setAltitudeInFeet(const bool val)
{
    altitudeInFeet = val;
    updateLabelCoordinates();
}
