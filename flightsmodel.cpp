#include "flightsmodel.h"
#include "flightsgenerator.h"
#include "constants.h"

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
        Flight flight(generateFlightId(), "TEST0" + std::to_string(i + 1));
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

    QMutexLocker flightsLocker(&flightsLock);
    emit readyFlights(flights);
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
    removeAlternativeRoute();

    optimisedFlightId = 1;

    Flight optimisedFlight;
    {
        QMutexLocker flightsLocker(&flightsLock);
        auto it = flights.find(optimisedFlightId);
        if(it != flights.end())
        {
            optimisedFlight = it.value();
            optimisedFlight.setId(OPTIMISER_FLIGHT_ID);
        }
    }
    if(optimisedFlight.getId() == OPTIMISER_FLIGHT_ID)
    {
        emit optimiseFlight(optimisedFlight);
    }
}

void FlightsModel::onFlightOptimised(const Flight &flight)
{
    {
        QMutexLocker flightsLocker(&flightsLock);
        flights.insert(OPTIMISER_FLIGHT_ID, flight);
    }

    sendUpdateFlightNotification(OPTIMISER_FLIGHT_ID);
    emit updated();
    emit alternativeRouteGenerated();
}

void FlightsModel::onFlightNotOptimised()
{
    emit alternativeRouteNotGenerated();
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
    sendUpdateFlightNotification(optimisedFlightId);

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

void FlightsModel::onClearFlights()
{
    clearFlights();
}

void FlightsModel::onUpdateOneFlight(const Flight & flight)
{
    updateOneFlight(flight);
    emit updated();
}

void FlightsModel::updateOneFlight(const Flight & flight)
{
    QMutexLocker flightsLocker(&flightsLock);
    auto it = flights.find(flight.getId());
    if(it == flights.end())
    {
        flights.insert(flight.getId(), flight);
    }
    else
    {
        it.value() = flight;
    }
}

void FlightsModel::sendUpdateFlightNotification(const Flight & flight)
{
    emit sendUpdateOneFlight(flight);
}

void FlightsModel::sendUpdateFlightNotification(const int id)
{
    Flight flightToSend;
    {
        QMutexLocker flightsLocker(&flightsLock);
        auto it = flights.find(id);
        if(it != flights.end())
        {
            flightToSend = it.value();
        }
    }

    emit sendUpdateOneFlight(flightToSend);
}
