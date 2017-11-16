#include "simulator.h"
#include "flightsmodel.h"

#include <iostream>
#include <unistd.h>

#include <QDateTime>

Simulator::Simulator(FlightsModel &model, QObject *parent) :
    QObject(parent),
    flightsModel(model),
    enabled(false),
    paused(false),
    simulationTime(0),
    simulationSpeed(1.0)
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
    simulationSpeed = 1.0;

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

    double currentSimulationSpeed = 1.0;
    {
        QMutexLocker controlLocker(&controlLock);
        currentSimulationSpeed = simulationSpeed;
    }

    QVector<WayPoint> & wayPoints = flight.getWayPoints();
    for(auto it = wayPoints.begin(); it != wayPoints.end(); ++it)
    {
        if(!it->isPassed())
        {
            int dX = abs(it->getCoordinates().getX() - coordinates.getX());
            int dY = abs(it->getCoordinates().getY() - coordinates.getY());
            double dist = sqrt(dX * dX + dY * dY);

            if(dist < POINTS_PASSED_THRESHOLD)
            {
                it->setPassed(true);

                coordinates.update(it->getCoordinates().getX(), it->getCoordinates().getY(), coordinates.getH());
                break;
            }

            double timeDiff = flight.getLastUpdateTime().msecsTo(QDateTime::currentDateTime()) / 1000.0;

            double k = currentSimulationSpeed * timeDiff * flight.getSpeed() / dist;

            std::cout << "flight x:y " << coordinates.getX() << ":" << coordinates.getY()
                      << " wpt x:y " << it->getCoordinates().getX() << ":" << it->getCoordinates().getY()
                      << " dist " << dist
                      << " k " << k << " timeDiff " << timeDiff << " spd " << currentSimulationSpeed
                      << " dx:dy " << dX << ":" << dY << std::endl;

            coordinates.update(coordinates.getX() + k * dX, coordinates.getY() + k * dY, coordinates.getH());
            std::cout << "updated flight x:y " << coordinates.getX() << ":" << coordinates.getY() << std::endl;

            break;
        }
    }

    flight.updateCoordinates(coordinates);
}

void Simulator::onDoubleSpeed()
{
    QMutexLocker controlLocker(&controlLock);
    simulationSpeed = 2.0;
}

void Simulator::onHalfSpeed()
{
    QMutexLocker controlLocker(&controlLock);
    simulationSpeed = 0.5;
}

void Simulator::onNormalSpeed()
{
    QMutexLocker controlLocker(&controlLock);
    simulationSpeed = 1.0;
}
