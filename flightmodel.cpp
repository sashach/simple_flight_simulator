#include "flightmodel.h"
#include "flightsgenerator.h"

#include <QMutexLocker>

#include <iostream>

FlightModel::FlightModel(QObject *parent):
      QObject(parent)
{

}

void FlightModel::clearFlights()
{
    QMutexLocker flightsLocker(&flightsLock);
    flights.clear();
}

void FlightModel::generateFlights()
{
    FlightsGenerator flightsGenerator;
    Flight flight;
    flightsGenerator.generate(flight, WORLD_SIZE);

    flight.updateFlightPosition(100, 100, 5000);

    QMutexLocker flightsLocker(&flightsLock);
    flights.push_back(flight);
}

void FlightModel::onGenerate()
{
    clearFlights();
    generateFlights();
    emit updated();
}

const QVector<Flight> &FlightModel::getFlights() const
{
    return flights;
}

QMutex & FlightModel::getLock()
{
    return flightsLock;
}
