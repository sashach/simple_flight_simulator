#include "simulator.h"
#include "flightsmodel.h"

#include <iostream>
#include <unistd.h>

#include <QDateTime>
#include <QDebug>

Simulator::Simulator(FlightsModel &model, QObject *parent) :
    QObject(parent),
    flightsModel(model),
    enabled(false),
    paused(false),
    simulationSpeed(1.0)
{
}

void Simulator::process()
{
    const int loopDelay = 500000;
    const qint64 simulationTimerStep = 500;
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
                usleep(loopDelay);
                continue;
            }
        }

        simulatorTime = simulatorTime.addMSecs(simulationSpeed * simulationTimerStep);

        if(processFlights())
        {
            flightsModel.onUpdate();
        }
        else
        {
            break;
        }

        usleep(loopDelay);
    }
}

void Simulator::onStart()
{
    enabled = true;
    paused = false;
    simulationSpeed = 1.0;

    simulatorStartTime = QDateTime::currentDateTime();
    simulatorStartTime.setTime(QTime(10, 0, 0, 0));
    simulatorTime = simulatorStartTime;
    resetFlightsUpdateTime();

    process();
}

void Simulator::resetFlightsUpdateTime()
{
    QMutexLocker flightsModelLocker(&flightsModel.getLock());
    QMap<int, Flight> & flights = flightsModel.getFlights();
    for(auto it = flights.begin(); it != flights.end(); ++it)
    {
        it.value().setLastUpdateTime(simulatorTime);
    }
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

bool Simulator::processFlights()
{
    qDebug() << "===============================";
    qDebug() << "time: " << simulatorTime;

    bool res = false;

    QMutexLocker flightsModelLocker(&flightsModel.getLock());
    QMap<int, Flight> & flights = flightsModel.getFlights();
    for(auto it = flights.begin(); it != flights.end() && it.value().getId() < FlightsModel::OPTIMISER_FLIGHT_ID; ++it)
    {
        res |= processOneFlight(it.value());
    }
    return res;
}

bool Simulator::processOneFlight(Flight & flight)
{
    Point3d coordinates = flight.getCoordinates();

    double currentSimulationSpeed = 1.0;
    {
        QMutexLocker controlLocker(&controlLock);
        currentSimulationSpeed = simulationSpeed;
    }

    bool processed = false;
    QVector<WayPoint> & wayPoints = flight.getWayPoints();
    for(auto it = wayPoints.begin(); it != wayPoints.end(); ++it)
    {
        if(!it->isPassed())
        {
            processed = true;

            if(it == wayPoints.begin())
            {
                it->setPassed(true);
                continue;
            }

            int dX = abs(it->getCoordinates().getX() - coordinates.getX());
            int dY = abs(it->getCoordinates().getY() - coordinates.getY());
            int dH = it->getCoordinates().getH() - coordinates.getH();
            double dist = sqrt(dX * dX + dY * dY);

            if(dist < POINTS_PASSED_THRESHOLD)
            {
                it->setPassed(true);

                coordinates.update(it->getCoordinates().getX(), it->getCoordinates().getY(), it->getCoordinates().getH());
                break;
            }

            double timeDiff = flight.getLastUpdateTime().msecsTo(simulatorTime) / 1000.0;

            if(timeDiff < std::numeric_limits<double>::epsilon())
            {
                continue;
            }

            flight.setSimulatorTimeDiff(simulatorStartTime.msecsTo(simulatorTime));

            double k = timeDiff * flight.getSpeed() / dist;

            qDebug()  << "flight x:y:h " << coordinates.getX() << ":" << coordinates.getY() << ":" << coordinates.getH()
                      << " wpt x:y " << it->getCoordinates().getX() << ":" << it->getCoordinates().getY()
                      << " dist " << dist
                      << " k " << k << " timeDiff " << timeDiff << " spd " << currentSimulationSpeed
                      << " dx:dy:dh " << dX << ":" << dY << ":" << dH;

            coordinates.update(coordinates.getX() + k * dX, coordinates.getY() + k * dY, coordinates.getH() + k * dH);
            qDebug() << "updated flight x:y:h " << coordinates.getX() << ":" << coordinates.getY() << ":" << coordinates.getH();

            break;
        }
    }

    flight.updateCoordinates(coordinates);
    flight.setLastUpdateTime(simulatorTime);

    return processed;
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
