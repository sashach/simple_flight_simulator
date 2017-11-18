#include "flightsmodel.h"
#include "flightsgenerator.h"
#include "constants.h"
#include "flightplanoptimiser.h"

#include <QMutexLocker>

#include <iostream>

FlightsModel::FlightsModel(QObject *parent):
      QObject(parent),
      lastFlightId(0),
      optimisedFlightId(0)
{

}

void FlightsModel::clearFlights()
{
    QMutexLocker flightsLocker(&flightsLock);
    flights.clear();
    lastFlightId = 0;
}

void FlightsModel::generateFlights()
{
    FlightsGenerator flightsGenerator;

    for(int i = 0; i < MAX_FLIGHTS_NUMBER; ++i)
    {
        Flight flight(generateFlightId(), "TEST0" + std::to_string(i));
        flightsGenerator.generate(flight, WORLD_SIZE, i * 100);

        QMutexLocker flightsLocker(&flightsLock);
        flights.insert(flight.getId(), flight);
    }
}

int FlightsModel::generateFlightId()
{
    return ++lastFlightId;
}

void FlightsModel::onGenerate()
{
    clearFlights();
    generateFlights();
    emit ready();
}

const QMap<int, Flight> &FlightsModel::getFlights() const
{
    return flights;
}

QMap<int, Flight> &FlightsModel::getFlights()
{
    return flights;
}

QMutex & FlightsModel::getLock()
{
    return flightsLock;
}

void FlightsModel::onUpdate()
{
    emit updated();
}

void FlightsModel::onOptimise()
{
    optimisedFlightId = 1;
    if(optimiseFlight())
    {
        emit updated();
        emit alternativeRouteGenerated();
    }
    else
    {
        emit alternativeRouteNotGenerated();
    }
}

bool FlightsModel::optimiseFlight()
{
    FlightPlanOptimiser optimiser;
    QMutexLocker flightsLocker(&flightsLock);
    return optimiser.createOptimisedCopy(flights, optimisedFlightId, OPTIMISER_FLIGHT_ID);
}

void FlightsModel::applyAlternativeRoute()
{
    QMutexLocker flightsLocker(&flightsLock);

    auto optimisedFlight = flights.find(OPTIMISER_FLIGHT_ID);
    auto originalFlight = flights.find(optimisedFlightId);
    if(optimisedFlight != flights.end() && originalFlight != flights.end())
    {
        originalFlight.value().deleteWayPoints();
        const QVector<WayPoint> & wayPoints = optimisedFlight.value().getWayPoints();
        for(auto it = wayPoints.begin(); it != wayPoints.end(); ++it)
        {
            if(it->isMandatory())
            {
                originalFlight.value().addWayPoint(*it);
            }
        }
    }
    flights.remove(OPTIMISER_FLIGHT_ID);
}

void FlightsModel::onApplyAlternativeRoute()
{
    applyAlternativeRoute();
    removeAlternativeRoute();
    emit updated();
}

void FlightsModel::removeAlternativeRoute()
{
    QMutexLocker flightsLocker(&flightsLock);
    flights.remove(OPTIMISER_FLIGHT_ID);
    optimisedFlightId = 0;
}

void FlightsModel::onCancelAlternativeRoute()
{
    removeAlternativeRoute();
    emit updated();
}
