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

    flight.updateCoordinates(100, 100, 5000);

    QMutexLocker flightsLocker(&flightsLock);
    flights.push_back(flight);
}

void FlightsModel::onGenerate()
{
    clearFlights();
    generateFlights();
    emit updated();
}

const QVector<Flight> &FlightsModel::getFlights() const
{
    return flights;
}

QMutex & FlightsModel::getLock()
{
    return flightsLock;
}

void FlightsModel::onRun()
{
    emit run();
}

void FlightsModel::onPause()
{
    emit pause();
}
