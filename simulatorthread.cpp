#include "simulatorthread.h"
#include "simulator.h"
#include "flightsmodel.h"

#include <QThread>

SimulatorThread::SimulatorThread(FlightsModel &model, QObject *parent) :
    QObject(parent),
    flightsModel(model)
{

}

void SimulatorThread::run()
{
    QThread * simulatorThread = new QThread();
    Simulator * simulator = new Simulator(flightsModel);

    simulator->moveToThread(simulatorThread);

    connect(simulator, SIGNAL(finished()), simulatorThread, SLOT(quit()));
    connect(simulator, SIGNAL(finished()), simulator, SLOT(deleteLater()));
    connect(simulatorThread, SIGNAL(finished()), simulatorThread, SLOT(deleteLater()));

    connect(this, SimulatorThread::start, simulator, Simulator::onStart);
    connect(this, SimulatorThread::stop, simulator, Simulator::onStop);
    connect(this, SimulatorThread::doubleSpeed, simulator, Simulator::onDoubleSpeed, Qt::DirectConnection);
    connect(this, SimulatorThread::halfSpeed, simulator, Simulator::onHalfSpeed, Qt::DirectConnection);
    connect(this, SimulatorThread::normalSpeed, simulator, Simulator::onNormalSpeed, Qt::DirectConnection);

    simulatorThread->start();
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
