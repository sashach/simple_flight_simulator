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

    connect(this, SimulatorThread::start, simulator, Simulator::onStart);

    simulatorThread->start();
}

void SimulatorThread::onStart()
{
    run();
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
