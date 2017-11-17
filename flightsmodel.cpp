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

    Flight flight1(1, "TEST01");
    flightsGenerator.generate(flight1, WORLD_SIZE);

    QMutexLocker flightsLocker(&flightsLock);
    flights.insert(flight1.getId(), flight1);
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
