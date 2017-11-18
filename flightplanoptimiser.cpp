#include "flightplanoptimiser.h"

#include <cstdlib>

FlightPlanOptimiser::FlightPlanOptimiser(QObject *parent) : QObject(parent)
{

}

void FlightPlanOptimiser::createOptimisedCopy(QMap<int, Flight> & flights, const int flightId, const int optimisedFlightId)
{
    auto oldOptimised = flights.find(optimisedFlightId);
    if(oldOptimised != flights.end())
    {
        flights.remove(oldOptimised.key());
    }

    auto it = flights.find(flightId);
    if(it != flights.end())
    {
        Flight optimisedFlight(it.value());
        optimisedFlight.setId(optimisedFlightId);
        optimiseRoute(optimisedFlight);
        flights.insert(optimisedFlightId, optimisedFlight);
    }
}

void FlightPlanOptimiser::optimiseRoute(Flight & flight)
{
    int nonPassedAhead = 0;
    QVector <WayPoint> & wayPoints = flight.getWayPoints();
    for(auto it = wayPoints.begin(); it != wayPoints.end() && (it + 3) != wayPoints.end(); ++it)
    {
        if(!it->isPassed())
        {
            if(nonPassedAhead > 2) // cannot bypass next point
            {
                double p = 1.0 * std::rand() / RAND_MAX;
                it->setMandatory(p >= 0.25);
            }
            ++nonPassedAhead;
        }
    }
}
