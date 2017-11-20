#include "simulatorthread.h"
#include "simulator.h"
#include "flightsmodel.h"
#include "simulatorserver.h"

#include <QThread>

SimulatorThread::SimulatorThread(FlightsModel &model, QObject *parent) :
    QObject(parent),
    flightsModel(model)
{

}

void SimulatorThread::run()
{
    Simulator * simulator = new Simulator(flightsModel);
#if 0
    QThread * simulatorThread = new QThread();
    simulator->moveToThread(simulatorThread);

    connect(simulator, SIGNAL(finished()), simulatorThread, SLOT(quit()));
    connect(simulator, SIGNAL(finished()), simulator, SLOT(deleteLater()));
    connect(simulatorThread, SIGNAL(finished()), simulatorThread, SLOT(deleteLater()));

    simulatorThread->start();
#endif

    connect(this, SIGNAL(start()), simulator, SLOT(onStart()));
    connect(this, SIGNAL(stop()), simulator, SLOT(onStop()), Qt::DirectConnection);
    connect(this, SIGNAL(pause()), simulator, SLOT(onPause()), Qt::DirectConnection);
    connect(this, SIGNAL(doubleSpeed()), simulator, SLOT(onDoubleSpeed()), Qt::DirectConnection);
    connect(this, SIGNAL(halfSpeed()), simulator, SLOT(onHalfSpeed()), Qt::DirectConnection);
    connect(this, SIGNAL(normalSpeed()), simulator, SLOT(onNormalSpeed()), Qt::DirectConnection);
}

void SimulatorThread::onStart()
{
    emit start();
}

void SimulatorThread::onPause()
{
    emit pause();
}

void SimulatorThread::onUpdate()
{
    emit update();
}

void SimulatorThread::onStop()
{
    emit stop();
}

void SimulatorThread::onDoubleSpeed()
{
    emit doubleSpeed();
}

void SimulatorThread::onHalfSpeed()
{
    emit halfSpeed();
}

void SimulatorThread::onNormalSpeed()
{
    emit normalSpeed();
}
