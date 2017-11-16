#include "simulator.h"
#include "flightsmodel.h"

#include <iostream>
#include <unistd.h>


Simulator::Simulator(FlightsModel &model, QObject *parent) :
    QObject(parent),
    flightsModel(model),
    enabled(false),
    paused(false),
    simulationTime(0)
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
        flightsModel.onUpdate();

        usleep(500000);
    }
}

void Simulator::onStart()
{
    enabled = true;
    paused = false;

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
}

void Simulator::processOneFlight(Flight & flight)
{
    Point3d coordinates = flight.getCoordinates();

    QVector<WayPoint> & wayPoints = flight.getWayPoints();
    for(auto it = wayPoints.begin(); it != wayPoints.end(); ++it)
    {
        if(!it->isPassed())
        {
            int dX = abs(it->getCoordinates().getX() - coordinates.getX());
            int dY = abs(it->getCoordinates().getY() - coordinates.getY());
            double dist = sqrt(dX * dX + dY * dY);

//            if(dX < 0 || dY < 0)
//            {
//                it->setPassed(true);
//                dX *= -1;
//                dY *= -1;
//            }
//            else
            if(dist < POINTS_PASSED_THRESHOLD)
            {
                it->setPassed(true);

                coordinates.update(it->getCoordinates().getX(), it->getCoordinates().getY(), coordinates.getH());
                break;
            }

            double k = flight.getSpeed() / dist;

            std::cout << "================================" << std::endl;
            std::cout << "point " << it->getName() << " dist " << dist << " K " << k << std::endl;
            std::cout << "\t flight x:y " << coordinates.getX() << ":" << coordinates.getY()
                      << " dx:dy " << dX << ":" << dY << std::endl;
            std::cout << "\t wpt x:y " << it->getCoordinates().getX() << ":" << it->getCoordinates().getY() << std::endl;

            coordinates.update(coordinates.getX() + k * dX, coordinates.getY() + k * dY, coordinates.getH());
            std::cout << "\t upd flight x:y " << coordinates.getX() << ":" << coordinates.getY() << std::endl;
            break;
        }
    }

    flight.updateCoordinates(coordinates);
}
