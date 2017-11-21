#include "flightplanoptimiser.h"

#include <cstdlib>

FlightPlanOptimiser::FlightPlanOptimiser(QObject *parent) : QObject(parent)
{

}

bool FlightPlanOptimiser::createOptimisedCopy(QMap<int, Flight> & flights, const int flightId, const int optimisedFlightId)
{
    bool res = false;
    auto it = flights.find(flightId);
    if(it != flights.end())
    {
        Flight optimisedFlight(it.value());
        optimisedFlight.setId(optimisedFlightId);

        if(optimiseRoute(optimisedFlight))
        {
            flights.insert(optimisedFlightId, optimisedFlight);
            res = true;
        }
    }
    return res;
}

bool FlightPlanOptimiser::optimiseRoute(Flight & flight)
{
    bool res = false;
    int nonPassedAhead = 0;
    QVector <WayPoint> & wayPoints = flight.getWayPoints();
    for(auto it = wayPoints.begin(); it != wayPoints.end() && (it + 3) != wayPoints.end(); ++it)
    {
        if(!it->isPassed())
        {
            if(nonPassedAhead > 2) // cannot bypass next point
            {
                double p = 1.0 * std::rand() / RAND_MAX;
                if(p < 0.25)
                {
                    it->setMandatory(false);
                    res = true;
                }
            }
            ++nonPassedAhead;
        }
    }
    return res;
}

bool FlightPlanOptimiser::optimiseFlight(Flight & flight)
{
    return optimiseRoute(flight);
}
