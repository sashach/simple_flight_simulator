#include "flightspomanager.h"

FlightsPOManager::FlightsPOManager(QObject *parent) : QObject(parent)
{
}

void FlightsPOManager::clearFlights()
{
    flights.clear();
}

void FlightsPOManager::addFlight(const Flight & flight)
{
    flights.push_back(flight);
}

const QVector<Flight> & FlightsPOManager::getFlights() const
{
    return flights;
}
