#include "flightsviewmodel.h"
#include "flightsmodel.h"

#include <QDebug>

FlightsViewModel::FlightsViewModel(FlightsModel &model, QObject *parent) :
    QObject(parent),
    flightsModel(model),
    optimisedFlightExists(false),
    menuFlightId(0)
{
    connect(&flightsModel, SIGNAL(ready()), this, SLOT(onFlightsUpdated()));
    connect(&flightsModel, SIGNAL(updated()), this, SLOT(onFlightsUpdated()));
}

void FlightsViewModel::onViewSizeChanged(const int width, const int height)
{
    coordinatesCalculator.updateScale(width, height);
    calculateScreenCoordinates();
}

const QMap<int, FlightPO> &FlightsViewModel::getFlights() const
{
    return flights;
}

void FlightsViewModel::onFlightsUpdated()
{
    optimisedFlightExists = false;

    QMutexLocker flightsModelLocker(&flightsModel.getLock());

    const QMap<int, Flight> & _flights = flightsModel.getFlights();
    for(auto it = _flights.begin(); it != _flights.end(); ++it)
    {
        if(it.value().getId() < FlightsModel::OPTIMISER_FLIGHT_ID)
        {
            auto flightIt = flights.find(it.key());
            if(flightIt == flights.end())
            {
                FlightPO flight(it.key());
                flight.updateFlight(it.value());
                flights.insert(it.key(), flight);
            }
            else
            {
                flightIt.value().updateFlight(it.value());
            }
        }
        else
        {
            optimisedFlightExists = true;
            optimisedFlight.updateFlight(it.value());
        }
    }

    calculateScreenCoordinates();
}

void FlightsViewModel::calculateScreenCoordinates()
{
    for(auto it = flights.begin(); it != flights.end(); ++it)
    {
        it.value().updateScreenCoordinates(coordinatesCalculator);
    }

    if(optimisedFlightExists)
    {
        optimisedFlight.updateScreenCoordinates(coordinatesCalculator);
    }

    emit flightsChanged();
}

void FlightsViewModel::onMousePressed(const int x, const int y, const QPoint &global)
{
    for(auto it = flights.begin(); it != flights.end(); ++it)
    {
        int dX = it.value().getX() - x;
        int dY = it.value().getY() - y;
        double dist = dX * dX + dY + dY;

        if(dist < MOUSE_CLICK_SENSITIVITY_SQRT)
        {
            menuFlightId = it.key();
            emit showMetersFeetMenu(global);
            break;
        }
    }

}

void FlightsViewModel::onMetersSelected()
{
    setAltitudeInFeet(false);
}

void FlightsViewModel::onFeetSelected()
{
    setAltitudeInFeet(true);
}

void FlightsViewModel::setAltitudeInFeet(const bool val)
{
    auto it = flights.find(menuFlightId);
    if(it != flights.end())
    {
        it.value().setAltitudeInFeet(val);
        emit flightsChanged();
    }
    menuFlightId = 0;
}

bool FlightsViewModel::isOptimisedFlightExists() const
{
    return optimisedFlightExists;
}

const FlightPO & FlightsViewModel::getOptimisedFlight() const
{
    return optimisedFlight;
}

void FlightsViewModel::clearFlights()
{
    flights.clear();
    optimisedFlightExists = false;
}
