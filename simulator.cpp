#include "simulator.h"
#include "flightsmodel.h"

#include <iostream>
#include <unistd.h>


Simulator::Simulator(FlightsModel &model, QObject *parent) :
    QObject(parent),
    flightsModel(model),
    enabled(false),
    paused(false)
{
}

void Simulator::process()
{
    while(true)
    {
        {
            QMutexLocker controlLocker(&controlLock);

            if(!enabled)
            {
                break;
            }
            if(paused)
            {
                usleep(100000);
                continue;
            }
        }

        processFlights();

        usleep(500000);
    }
}

void Simulator::onStart()
{
    enabled = true;
    paused = false;

    //emit start();
    process();
}

void Simulator::onPause()
{
    QMutexLocker controlLocker(&controlLock);
    paused = !paused;
}

void Simulator::onStop()
{
    QMutexLocker controlLocker(&controlLock);
    enabled = false;
}

void Simulator::processFlights()
{
    QMutexLocker flightsModelLocker(&flightsModel.getLock());

    QVector<Flight> & flights = flightsModel.getFlights();
    for(auto it = flights.begin(); it != flights.end(); ++it)
    {
        processOneFlight(*it);
    }

    flightsModel.onUpdate();
}

void Simulator::processOneFlight(Flight & flight)
{
    Point3d coordinates = flight.getCoordinates();
    coordinates.update(coordinates.getX() + 10, coordinates.getY() + 10, coordinates.getH());
    flight.updateCoordinates(coordinates);
}
