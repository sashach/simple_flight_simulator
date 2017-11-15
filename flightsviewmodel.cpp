#include "flightsviewmodel.h"
#include "flightsmodel.h"

FlightsViewModel::FlightsViewModel(FlightsModel &model, QObject *parent) :
    QObject(parent),
    flightsModel(model)
{
    connect(&flightsModel, FlightsModel::updated, this, onFlightsUpdated);
}

void FlightsViewModel::onViewSizeChanged(const int width, const int height)
{
    coordinatesCalculator.updateScale(width, height);
    calculateScreenCoordinates();
}

const QVector<FlightPO> &FlightsViewModel::getFlights() const
{
    return flights;
}

void FlightsViewModel::onFlightsUpdated()
{
    flights.clear();

    QMutexLocker flightsModelLocker(&flightsModel.getLock());

    const QVector<Flight> & _flights = flightsModel.getFlights();
    for(auto it = _flights.begin(); it != _flights.end(); ++it)
    {
        FlightPO flight;
        flight.updateFlight(*it);
        flights.push_back(flight);
    }

    calculateScreenCoordinates();
}

void FlightsViewModel::calculateScreenCoordinates()
{
    for(auto it = flights.begin(); it != flights.end(); ++it)
    {
        it->updateScreenCoordinates(coordinatesCalculator);
    }

    emit flightsChanged();
}
