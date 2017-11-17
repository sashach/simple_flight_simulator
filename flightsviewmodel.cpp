#include "flightsviewmodel.h"
#include "flightsmodel.h"

#include <QDebug>

FlightsViewModel::FlightsViewModel(FlightsModel &model, QObject *parent) :
    QObject(parent),
    flightsModel(model),
    menuFlightId(0)
{
    connect(&flightsModel, FlightsModel::ready, this, onFlightsUpdated);
    connect(&flightsModel, FlightsModel::updated, this, onFlightsUpdated);
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
    QMutexLocker flightsModelLocker(&flightsModel.getLock());

    const QMap<int, Flight> & _flights = flightsModel.getFlights();
    for(auto it = _flights.begin(); it != _flights.end(); ++it)
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

    calculateScreenCoordinates();
}

void FlightsViewModel::calculateScreenCoordinates()
{
    for(auto it = flights.begin(); it != flights.end(); ++it)
    {
        it.value().updateScreenCoordinates(coordinatesCalculator);
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
