#include "directservice.h"
#include "flightplanoptimiser.h"
#include "flightsmodel.h"


DirectService::DirectService(QObject *parent) : QObject(parent)
{

}

bool DirectService::directFlight(Flight & optimisedFlight) const
{
    FlightPlanOptimiser optimiser;
    return optimiser.optimiseFlight(optimisedFlight);
}

void DirectService::onOptimise(const Flight &flight)
{
    Flight _flight(flight);
    if(directFlight(_flight))
    {
        emit flightOptimised(_flight);
        emit alternativeRouteGenerated();
    }
    else
    {
        emit alternativeRouteNotGenerated();
    }
}
