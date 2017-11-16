#include "flightsmodel.h"
#include "flightsgenerator.h"
#include "constants.h"

#include <QMutexLocker>

#include <iostream>

FlightsModel::FlightsModel(QObject *parent):
      QObject(parent)
{

}

void FlightsModel::clearFlights()
{
    QMutexLocker flightsLocker(&flightsLock);
    flights.clear();
}

void FlightsModel::generateFlights()
{
    FlightsGenerator flightsGenerator;
    Flight flight;
    flightsGenerator.generate(flight, WORLD_SIZE);

    flight.updateCoordinates(0, 0, 5000);

    QMutexLocker flightsLocker(&flightsLock);
    flights.push_back(flight);
}

void FlightsModel::onGenerate()
{
    clearFlights();
    generateFlights();
    emit ready();
}

const QVector<Flight> &FlightsModel::getFlights() const
{
    return flights;
}

QVector<Flight> &FlightsModel::getFlights()
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
